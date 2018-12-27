// quick_sort_randomized.h
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

#ifndef QUICK_SORT_RANDOMIZED_H_
#define QUICK_SORT_RANDOMIZED_H_

#include "quick_sort.h"

namespace hedger
{
class QuickSortRandomized : public QuickSort
{
 public:
  QuickSortRandomized();
  ~QuickSortRandomized();
  const char *GetName() { return "Quick Sort Randomized"; }
 protected:
  int RandomizedPartition(
    hedger::S_T *arr,
    int start,
    int end
  );
  virtual void SortRecurse(hedger::S_T *arr, int start, int end);
};
}

#endif // QUICK_SORT_H_
