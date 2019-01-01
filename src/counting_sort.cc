// counting_sort.cc
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
#include <assert.h>

#include <cstddef>
#include <vector>

#include "counting_sort.h"

namespace hedger {

// Constructor
CountingSort::CountingSort() {
};

// Destructor
CountingSort::~CountingSort() {
}

// Test
// Implementation of Algo's pure virtual Test()
// Entry: pointer to array to sort
//        size of array in hedger::S_T units
int CountingSort::Test(hedger::S_T *array, size_t size, hedger::S_T range)
{
  int result = 0;

  Sort(array, size, 0, range);

  return result;
}

//
// Class-specific Implementation
//

// Sort
//
// Counts instances of unique elements and sorts them.
// Must know range in advance for this algorithm.
//
// Entry: pointer to array
//        size
//        lowest item value
//        highest item value (inclusive)
// Exit:  arr sorted
void CountingSort::Sort(
  hedger::S_T *arr,
  int size,
  hedger::S_T range_low,
  hedger::S_T range_hi
)
{
  assert(range_hi > range_low);

  int range_hi_adjusted = range_hi - range_low;
  // This allocates an array of unique element counts and clears it.
  int *count_arr = (int *) calloc(range_hi_adjusted + 1, sizeof(int));
  assert(count_arr);
  // Here we count how many of each element and save the counts in count_arr.
  for (auto i = 0; i < size; ++i) {
    ++count_arr[arr[i] - range_low];
  }
#if 1
  // Change count[i] so that count[i] now contains actual
  //  position of this digit in output[]
  for (auto i = 1; i < range_hi_adjusted; i++)
    count_arr[i] += count_arr[i - 1];

  // Write the output
  int out_index = 0;
  int count_index = 0;
  int next_delta_index = -1;
  hedger::S_T write_value = 0;
  while (out_index < size) {
    while (out_index >= next_delta_index) {
      next_delta_index = count_arr[count_index];
      write_value = count_index;
      ++count_index;
    }
    arr[out_index] = write_value;
    ++out_index;
  }
#else
  // ALTERNATIVE IMPLEMENTATION; AVOIDS EXTRA STAIRSTEP TABLE
  // GENERATION LOOP.
  // Now, we iterate through the count array and write the output.
  // For convenience, we write to the array passed in
  hedger::S_T write_value = range_low;
  hedger::S_T i;
  int out_index;
  int write_count;
  i = out_index = 0;
  while (out_index < size) {  // skips past non-occuring values
    while (i < range_hi_adjusted && !count_arr[i]) {
      ++i;
    }
    if (i < range_hi_adjusted ) { // sets # of repetitions to write
      write_value = i + range_low;
      write_count = count_arr[i] + 1;
      ++i;
    }
    while (--write_count) { // writes write_count repetitions
      arr[out_index] = write_value;
      ++out_index;
    }
  }
#endif
  // Clean up and exit
  free(count_arr);
}
} // namespace hedger
