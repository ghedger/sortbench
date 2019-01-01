// radix_sort.h
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

#ifndef RADIX_SORT_H_
#define RADIX_SORT_H_

#include "algo.h"

namespace hedger
{
class RadixSort : public Algo
{
 public:
  RadixSort();
  virtual ~RadixSort();
  virtual int Test(hedger::S_T *arr, size_t size, hedger::S_T range = 0);
  virtual const char *GetName() { return "Radix Sort"; }
 protected:
  hedger::S_T GetMax(hedger::S_T *arr, int n);
  void CountSort(int arr[], int n, int exp, int radix);
  virtual void Sort(hedger::S_T *arr, int start, int radix);
};
}

#endif // RADIX_SORT_H_
