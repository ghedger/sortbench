// quick_sort.h
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

#ifndef QUICK_SORT_H_
#define QUICK_SORT_H_

#include "algo.h"

namespace hedger
{
class QuickSort : public Algo
{
 public:
  QuickSort();
  virtual ~QuickSort();
  virtual int Test(hedger::S_T *arr, size_t size, hedger::S_T range = 0);
  virtual const char *GetName() { return "Quick Sort"; }
 protected:
  virtual int Partition(int start, int end);
  virtual void Sort(hedger::S_T *arr, int start, int end);
  virtual void SortRecurse(int start, int end);
  virtual void Swap(int index_a, int index_b);
};
}

#endif // QUICK_SORT_H_
