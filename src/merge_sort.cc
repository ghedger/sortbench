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
  int * tmp_arr = NULL;
  int i = 0;
  int l1 = start;
  int r1 = mid;
  int l2 = mid + 1;
  int r2 = end;

  tmp_arr = new int[ end - start + 1 ];

  while((l1 <= r1) && (l2 <= r2))
  {
    if(arr[l1] < arr[l2])
      tmp_arr[i++] = arr[l1++];
    else
      tmp_arr[i++] = arr[l2++];
  }

  while(l1 <= r1)
    tmp_arr[i++] = arr[l1++];
  while(l2 <= r2)
    tmp_arr[i++] = arr[l2++];

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
    sort(arr, start, mid);
    sort(arr, mid+1, end);

    // printf( " merge: %d %d %d\n", start, mid, end );
    merge(arr, start, mid, end);
  }
}
} // namespace hedger
