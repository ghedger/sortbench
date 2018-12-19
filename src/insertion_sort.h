// insertion_sort.h
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


#ifndef INSERTION_SORT_H_
#define INSERTION_SORT_H_

#include "algo.h"

namespace hedger
{
class InsertionSort : public Algo
{
 public:
  InsertionSort();
  ~InsertionSort();
  int Test(hedger::S_T *arr, size_t size, hedger::S_T range = 0);
  const char *GetName() { return "Insertion Sort"; }
 protected:
  int Partition(hedger::S_T *arr, int start, int end);
  void Sort(hedger::S_T *arr, int start, int end);
  void SortRecurse(hedger::S_T *arr, int start, int end);
 private:
  inline void Swap(hedger::S_T *arr, int index_a, int index_b);
};
}

#endif // INSERTION_SORT_H_
