// quick_sort.cc
//
// This implements a naive quick sort on an array of datatype hedger::S_T.
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

#include "quick_sort.h"

namespace hedger {

QuickSort::QuickSort() {
};

QuickSort::~QuickSort() {
}

int QuickSort::Test(int *array, std::size_t size)
{
  int result = 0;

  Sort( array, 0, size - 1 );

  return result;
}

//
// Class-specific Implementation
//

// findPartition
// Find the next partition for sorting
// Entry: pointer to array
//        start index
//        end index
int QuickSort::FindPartition(hedger::S_T *arr, int start, int end)
{
  int pivot_mag = arr[end];
  int partition = start;
  int i;
  hedger::S_T swap;

  for (i = start; i < end; i++) {
    if (arr[i] <= pivot_mag) {
      swap = arr[i];
      arr[i] = arr[partition];
      arr[partition] = swap;
      partition++;
    }
  }

  swap = arr[end];
  arr[end] = arr[partition];
  arr[partition] = swap;
  return partition;
}

// sort
// Perform the sorting.
// TODO: Apply R.C. Singleton's optimization (Knuth Vol.3 2nd Ed. p.123) or
//   a variant thereof to avoid the O(n^2) penalty for an already-sorted array.
//
// Entry: pointer to array
//        start index
//        end index
void QuickSort::Sort(hedger::S_T *arr, int start, int end)
{
  if (start < end) {
    int partition = FindPartition(arr, start, end);
    Sort(arr, start, partition - 1);
    Sort(arr, partition + 1, end);
  }
}
} // namespace hedger
