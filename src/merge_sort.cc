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
#include <cstddef>

#include "merge_sort.h"

namespace hedger {

MergeSort::MergeSort() {
};

MergeSort::~MergeSort() {
}

int MergeSort::test(int *array, std::size_t size)
{
  int result = 0;

  sort( array, 0, size - 1 );

  return result;
}

//
// Class-specific Implementation
//

// merge
// Merge two subarrays.  Typically called by the mergesort() function.
// Entry: start index
//        middle index
//        end index
// Exit:  -
void MergeSort::merge(int *arr, int start, int mid, int end)
{
  int *tmp_arr = NULL;
  int i = 0;
  int left1 = start;
  int right1 = mid;
  int left2 = mid + 1;
  int right2 = end;

  tmp_arr = new int[ end - start + 1 ];

  while((left1 <= right1) && (left2 <= right2))
  {
    if(arr[left1] < arr[left2])
      tmp_arr[i++] = arr[left1++];
    else
      tmp_arr[i++] = arr[left2++];
  }

  while(left1 <= right1)
    tmp_arr[i++] = arr[left1++];
  while(left2 <= right2)
    tmp_arr[i++] = arr[left2++];

  for(i = start; i <= end; i++) {
    arr[i] = tmp_arr[i - start];
  }

  delete tmp_arr;
}

// MergeSort::sort
//
// Outer merge sort process: break down into sub arrays, then call
// the merge function.
// (Recursive)
//
// Entry: pointer to array
//        start index (typically 0)
//        end index (typically end-1)
// Exit:  -
void MergeSort::sort(int *arr, int start, int end)
{
  int mid = 0;

  if(start < end)
  {
    mid = (start + end) / 2;
    printf("S: %d  M: %d E: %d\n",start, mid, end);
    sort(arr, start, mid);
    sort(arr, mid+1, end);

    // printf( " merge: %d %d %d\n", start, mid, end );
    merge(arr, start, mid, end);
  } else {
    printf("(zero-length subarray; exit)\n");
  }
}
} // namespace hedger
