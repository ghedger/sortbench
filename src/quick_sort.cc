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

// Test
// Implement the Test function as dictated by the Algo parent class
// Entry: pointer to array
//        size of array
// Exit:  Result of test
//
int QuickSort::Test(hedger::S_T *array, size_t size, hedger::S_T range)
{
  int result = 0;
  Sort( array, 0, size - 1 );
  return result;
}

//
// Class-specific Implementation
//

// Swap
// Swap two array values identified by index
// Entry: pointer to array
//        index a
//        index b
void QuickSort::Swap(hedger::S_T *arr, int index_a, int index_b)
{
  hedger::S_T swap = arr[index_a];
  arr[index_a] = arr[index_b];
  arr[index_b] = swap;
}

// findPartition
// Find the next partition for sorting
// Entry: pointer to array
//        start index
//        end index
int QuickSort::Partition(hedger::S_T *arr, int start, int end)
{
  int pivot_mag = arr[end];     // magnitude: lesser, left; greater, right
  int partition = start;

  for (int i = start; i < end; ++i) {
    if (arr[i] <= pivot_mag) {
      // Need to swap current index value with partition index value
      // to get the greater value to the right of the partition
      // We place the lesser value at the partition index and move
      // the partition to the right.
      Swap(arr, i, partition);
      partition++;
    }
  }

  // Swap the last element with the partition.
  // At this point, all the items to the left of the partition will be less
  // than those to the right.
  Swap(arr, end, partition);
  return partition;
}

// SortRecurse
// Perform the sorting.
// TODO: Apply R.C. Singleton's optimization (Knuth Vol.3 2nd Ed. p.123) or
//   a variant thereof to avoid the O(n^2) penalty for an already-sorted array.
// Entry: pointer to array
//        start index
//        end index
void QuickSort::SortRecurse(hedger::S_T *arr, int start, int end)
{
  if (start < end) {
    int partition = Partition(arr, start, end);
    Sort(arr, start, partition - 1);
    Sort(arr, partition + 1, end);
  }
}

// sort
// API entry for sort.
// Entry: pointer to array
//        start index
//        end index
void QuickSort::Sort(hedger::S_T *arr, int start, int end)
{
  if ((start < end) && nullptr != arr)
    SortRecurse(arr, start, end);
}
} // namespace hedger
