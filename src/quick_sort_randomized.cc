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
#include <math.h>
#include <cstddef>

#include "quick_sort_randomized.h"

namespace hedger {

QuickSortRandomized::QuickSortRandomized() {
}

QuickSortRandomized::~QuickSortRandomized() {
}

// RadomizedPartition
// Take a partition from a random spot within the distribution.
// (Per T. Corman "Introduction to Algorithms" p. 179)
// Entry: array
//        start index
//        end index
// Exit: partition index
int QuickSortRandomized::RandomizedPartition(
  hedger::S_T *arr,
  int start,
  int end
)
{
    int i = (rand() % (end - start)) + start;
    Swap(arr, i, end - 1);
    return Partition(arr, start, end);
}

// SortRecurse
// Perform the sorting.
// TODO: Apply R.C. Singleton's optimization (Knuth Vol.3 2nd Ed. p.123) or
//   a variant thereof to avoid the O(n^2) penalty for an already-sorted array.
// Entry: pointer to array
//        start index
//        end index
void QuickSortRandomized::SortRecurse(hedger::S_T *arr, int start, int end)
{
  if (start < end) {
    int partition = RandomizedPartition(arr, start, end);
    Sort(arr, start, partition - 1);
    Sort(arr, partition + 1, end);
  }
}
} // namespace hedger
