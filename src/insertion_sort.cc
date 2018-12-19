// insertion_sort.cc
//
// This implements insertion sort on an array.
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

#include "insertion_sort.h"

namespace hedger {

InsertionSort::InsertionSort() {
};

InsertionSort::~InsertionSort() {
}

// Test
// Implement the Test function as dictated by the Algo parent class
// Entry: pointer to array
//        size of array
// Exit:  Result of test
//
int InsertionSort::Test(hedger::S_T *array, size_t size, hedger::S_T range)
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
void InsertionSort::Swap(hedger::S_T *arr, int index_a, int index_b)
{
  hedger::S_T swap = arr[index_a];
  arr[index_a] = arr[index_b];
  arr[index_b] = swap;
}

// Sort
// Entry: pointer to array
//        start index
//        end index
void InsertionSort::Sort(hedger::S_T *arr, int start, int end)
{
  if ((start < end) && nullptr != arr) {
    for (auto j = 1; j <= end; j++) {
      hedger::S_T key = arr[j];
      // Insert arr[j] into the sorted sequence.
      auto i = j - 1;
      while (i > 0 && arr[i] > key) {
        arr[i + 1] = arr[i];
        --i;
      }
      arr[i + 1] = key;
    }
  }
}
} // namespace hedger
