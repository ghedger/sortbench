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

#include <cstddef>
#include <vector>

#include "merge_sort.h"

namespace hedger {

// Constructor
MergeSort::MergeSort() {
};

// Destructor
MergeSort::~MergeSort() {
}

// Test
// Implementation of Algo's pure virtual Test()
// Entry: pointer to array to sort
//        size of array in hedger::S_T units
int MergeSort::Test(hedger::S_T *array, std::size_t size)
{
  int result = 0;

  Sort( array, 0, size - 1 );

  return result;
}

//
// Class-specific Implementation
//

// Alloca
// Inline safe alloca
void *MergeSort::Alloca(size_t size)
{
  return alloca(size);
}


// Merge
// Merge two subarrays.  Typically called by the mergesort() function.
// Entry: start index
//        middle index
//        end index
// Exit:  -
void MergeSort::Merge(hedger::S_T *arr, int start, int mid, int end)
{
  hedger::S_T *tmp_arr;
  int left1 = start;        // left of left-half <- start
  int right1 = mid;         // right of left-half <- mid
  int left2 = mid + 1;      // left of right-half <- mid + 1
  int right2 = end;         // right of right-half <- end

  // Reserve maximum amount of space in vector (prevent unecessary growth resizes).
  // tmp_arr.reserve(end - start + 1);
  // NOTE: alloca is not best choice for big arrays...  heap and vector are
  // safer alternatives, but far less effient (> 3X slower in testing)
  tmp_arr = (hedger::S_T *)alloca((end - start + 1) * sizeof(hedger::S_T));
  hedger::S_T *next_tmp = tmp_arr;

  // Go through and save either left subarray or right subarray into swap array
  // according to the least at each index in the respective subarrays.
  while((left1 <= right1) && (left2 <= right2))
  {
    if(arr[left1] < arr[left2])
      *next_tmp++ = arr[left1++];    // save arr[left1]
    else
      *next_tmp++ = arr[left2++];    // save arr[left2]
  }

  // Now, save off the rest of the data in the swap array
  // from each of the two subarrays
  while(left1 <= right1)
    *next_tmp++ = arr[left1++];      // save arr[left1]
  while(left2 <= right2)
    *next_tmp++ = arr[left2++];      // save arr[left2]

  // Finally, recover from swap array, in essence popping the data off the stack i
  // in reverse order and storing it in the array.
  memcpy(&arr[start], tmp_arr, sizeof(hedger::S_T) * (end - start + 1));
}

// Sort
//
// Outer merge sort process: break down into sub arrays, then call
// the merge function.
// (Recursive)
//
// Entry: pointer to array
//        start index (typically 0)
//        end index (typically end-1)
// Exit:  -
void MergeSort::Sort(hedger::S_T *arr, int start, int end)
{
  int mid = 0;
  if(start < end)
  {
    mid = (start + end) / 2;
    // We're going to break the data set into progressively smaller pieces,
    // merging each as we unwind.
    Sort(arr, start, mid);
    Sort(arr, mid + 1, end);

    // On the unwind, we merge each of the subarrays, breaking each sub array into
    // two in the Merge function.  As the Sort function unwinds, the arrays processed
    // by merge get progressively larger until the final Merge, leaving a perfectly
    // sorted array.
    Merge(arr, start, mid, end);
  }
}
} // namespace hedger
