// heap_sort.cc
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

#include "heap_sort.h"

namespace hedger {

HeapSort::HeapSort() {
}

HeapSort::~HeapSort() {
}

// Test
// Implement the Test function as dictated by the Algo parent class
// Entry: pointer to array
//        size of array
// Exit:  Result of test
//
int HeapSort::Test(hedger::S_T *array, size_t size, hedger::S_T range)
{
  int result = 0;
  Sort(array, size);
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
void HeapSort::Swap(hedger::S_T *arr, int index_a, int index_b)
{
  hedger::S_T swap = arr[index_a];
  arr[index_a] = arr[index_b];
  arr[index_b] = swap;
}


void HeapSort::MaxHeapify(hedger::S_T *arr, int size, int index)
{
  int left = Left(index);
  int right = Right(index);
  hedger::S_T largest;
  if ((left < size) && (arr[left] > arr[index]))
    largest = left;
  else
    largest = index;
  if ((right < size) && (arr[right] > arr[largest]))
    largest = right;
  if (largest != index) {
    Swap(arr, index, largest);
    MaxHeapify(arr, size, largest);
  }
}

void HeapSort::BuildMaxHeap(hedger::S_T *arr, int size)
{
  for (auto i = (size >> 1); i >= 0; --i) {
    MaxHeapify(arr, size, i);
  }
}

// sort
// API entry for sort.
// Entry: pointer to array
//        start index
//        end index
void HeapSort::Sort(hedger::S_T *arr, int size)
{
  int heap_size = size;
  if (size && nullptr != arr) {
    BuildMaxHeap(arr, size);
    for (auto i = size - 1; i >= 1; --i) {
      Swap(arr, i, 0);
      heap_size -= 1;
      MaxHeapify(arr, heap_size, 0);
    }
  }
}
} // namespace hedger
