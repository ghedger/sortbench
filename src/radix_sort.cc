// radix_sort.cc
//
// This implements a naive radix sort on an array of datatype hedger::S_T.
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

#include "radix_sort.h"

namespace hedger {

RadixSort::RadixSort() {
}

RadixSort::~RadixSort() {
}

// Test
// Implement the Test function as dictated by the Algo parent class
// Entry: pointer to array
//        size of array
// Exit:  Result of test
//
int RadixSort::Test(hedger::S_T *array, size_t size, hedger::S_T range)
{
  int result = 0;
  Sort(array, size, 256);
  return result;
}

//
// Class-specific Implementation
//

// GetMax
// A utility function to get maximum value in arr[]
hedger::S_T RadixSort::GetMax(hedger::S_T *arr, int size)
{
  int max = arr[0];
  for (int i = 1; i < size; i++)
    if (arr[i] > max)
      max = arr[i];
  return max;
}

// CountSort
// Perform a counting sort on the given data
// the digit represented by exp.
void RadixSort::CountSort(int arr[], int size, int exp, int radix)
{
  int output[size]; // output array
  int i, count[radix] = {0};

  // Store count of occurrences in count[]
  for (i = 0; i < size; i++)
    count[ (arr[i] / exp) % radix ]++;

  // Change count[i] so that count[i] now contains actual
  //  position of this digit in output[]
  for (i = 1; i < radix; i++)
    count[i] += count[i - 1];

  // Build the output array
  for (i = size - 1; i >= 0; i--)
  {
    output[count[ (arr[i] / exp) % radix ] - 1] = arr[i];
    count[ (arr[i] / exp) % radix ]--;
  }

  // Copy the output array to arr[], so that arr[] now
  // contains sorted numbers according to current digit
  for (i = 0; i < size; i++)
    arr[i] = output[i];
}

// Sort
// API entry for sort.
// Entry: pointer to array
//        start index
//        end index
void RadixSort::Sort(hedger::S_T *arr, int size, int radix)
{
  if (size && nullptr != arr) {

    hedger::S_T m = GetMax(arr, size);

    // Do counting sort for every digit. Note that instead
    // of passing digit number, exp is passed. exp is radix^i
    // where i is current digit number
    for (int exp = 1; m / exp > 0; exp *= radix)
      CountSort(arr, size, exp, radix;
  }
}
} // namespace hedger
