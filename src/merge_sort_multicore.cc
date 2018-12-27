// merge_sort.cc
//
// This implements a merge sort on an array of items of type hedger::S_T.
//
// This file is part of sortbench.
//
// Sortbench is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Sortbench is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with sortbench.  If not, see <https://www.gnu.org/licenses/>.
//
// Copyright (C) 2018 Gregory Hedger
//

#include <stdio.h>
#include <alloca.h>
#include <unistd.h>
#include <memory.h>
#include <malloc.h>
#include <pthread.h>
#include <sched.h>
#include <assert.h>

#include <cstddef>

#include "merge_sort_multicore.h"
namespace hedger {

// Static variable definitions
volatile int MergeSortMultiCore::thread_tot_ = 0;
const int MergeSortMultiCore::kThreadMax = 6;
Lock *MergeSortMultiCore::merge_lock_;

// Constructor
MergeSortMultiCore::MergeSortMultiCore() {
};

// Destructor
MergeSortMultiCore::~MergeSortMultiCore() {
}

// Test
// Implementation of Algo's pure virtual Test()
// Entry: pointer to array to sort
//        size of array in hedger::S_T units
int MergeSortMultiCore::Test(hedger::S_T *array, size_t size, hedger::S_T range)
{
  int result = 0;

  Sort(array, size);

  return result;
}

//
// Class-specific Implementation
//

// Sort
// Entry point for sort start.
// Sets up our local pool so we aren't constantly allocating from heap
// Entry: pointer to array
//        size of array in elements
void MergeSortMultiCore::Sort(hedger::S_T *arr, int size)
{
  if (arr && size)
  {
    arr_ = arr;
    MergeSortMultiParams params;
    params.arr =        arr;
    params.start =      0;
    params.end =        size - 1;
    params.merge_sort = this;
    SortRecurse((void *)&params);
  }
}

// Merge
// Merge two subarrays.  Typically called by the mergesort() function.
// Entry: pointer to array
//        start index
//        middle index
//        end index
// Exit:  -
void MergeSortMultiCore::Merge(int start, int mid, int end)
{
  hedger::S_T *tmp_arr;     // pointer to temp array
  int left1 = start;        // left of left-half <- start
  int right1 = mid;         // right of left-half <- mid
  int left2 = mid + 1;      // left of right-half <- mid + 1
  int right2 = end;         // right of right-half <- end

  // Allocate a temporary array for swapping out and re-ordering words
  // to be copied back to original array.
  // NOTE: alloca is much faster but non-standard and not safe.
  //tmp_arr = Pop();
  tmp_arr = (hedger::S_T *) malloc((end - start + 1) * sizeof(hedger::S_T));
  hedger::S_T *next_tmp = tmp_arr;

  // Go through and save either left subarray or right subarray into swap array
  // according to the least at each index in the respective subarrays.
  while((left1 <= right1) && (left2 <= right2)) {
    if(arr_[left1] < arr_[left2])
      *next_tmp++ = arr_[left1++];    // save arr[left1]
    else
      *next_tmp++ = arr_[left2++];    // save arr[left2]
  }

  // Now, save off the rest of the data in the swap array
  // from each of the two subarrays
  while(left1 <= right1)
    *next_tmp++ = arr_[left1++];      // save arr[left1]
  while(left2 <= right2)
    *next_tmp++ = arr_[left2++];      // save arr[left2]

  // Finally, recover what we've saved, sorted, from the swap array.
  memcpy(&arr_[start], tmp_arr, sizeof(hedger::S_T) * (end - start + 1));
  free(tmp_arr);
  //Push(tmp_arr);
}

// Sort
// Outer merge sort process: break down into sub arrays, then instantiate
// threads to do the same on divide-and-conquer basis.
// Entry: pointer to params containing:
//          - array
//          - start index (typically 0)
//          - end index (typically end-1)
// Exit:  nullptr (ignored)
void *MergeSortMultiCore::SortRecurse(void *params)
{
  MergeSortMultiParams *sort_params = (MergeSortMultiParams *)params;
  if(sort_params->start < sort_params->end)
  {
    int mid = (sort_params->start + sort_params->end) / 2;
    // We're going to break the data set into progressively smaller pieces,
    // merging each as we unwind.

    // This sets up the thread paramter blocks telling the threads which
    // part of the array they are assigned.
    pthread_t thread_1, thread_2;
    MergeSortMultiParams threadparams_1, threadparams_2;
    threadparams_1.arr = threadparams_2.arr = sort_params->arr;
    threadparams_1.start = sort_params->start;
    threadparams_1.end = mid;
    threadparams_1.merge_sort = sort_params->merge_sort;
    threadparams_2.start = mid + 1;
    threadparams_2.end = sort_params->end;
    threadparams_2.merge_sort = sort_params->merge_sort;

    if (GetThreadTot() < kThreadMax) {
      SetThreadTot(GetThreadTot() + 2);
      // Here we will instantiate the threads - two of them, one of the left,
      // one for the right with mid as the partition.
      int error = pthread_create(
        &thread_1,
        NULL,
        &MergeSortMultiCore::SortRecurse,
        (void *)&threadparams_1);
      if (error) {
        // TODO: LOG ERROR
      }
      error = pthread_create(
        &thread_2,
        NULL,
        &MergeSortMultiCore::SortRecurse,
        (void *)&threadparams_2);
      if (error) {
        // TODO: LOG ERROR
      }
     // This re-syncs with the two child threads we spawned.  This must be
     // done before Merge() is called
     void *result;
     pthread_join(thread_2,&result);
     pthread_join(thread_1,&result);
     SetThreadTot(GetThreadTot() - 2);
    } else {
      // If we're here, it means we've exceeded our
      // thread cap, so we'll execute these sorts in this thread.
      SortRecurse((void *)&threadparams_1);
      SortRecurse((void *)&threadparams_2);
    }
    // Merge the subarrays on unwind.
    sort_params->merge_sort->Merge(
      sort_params->start,
      mid,
      sort_params->end
    );
  }
  return nullptr; // return value is ignored
}
} // namespace hedger
