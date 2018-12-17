// counting_sort.h
//
// Counting sort implementation class header.
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

#ifndef COUNTING_SORT_H_
#define COUNTING_SORT_H_

#include "algo.h"

namespace hedger
{
class CountingSort : public Algo
{
 public:
  CountingSort();
  virtual ~CountingSort();
  int Test(hedger::S_T *arr, std::size_t size);
  void Sort(
    hedger::S_T *arr,
    int size,
    hedger::S_T range_low,
    hedger::S_T range_hight
  );
};
}

#endif // COUNTING_SORT_H_
