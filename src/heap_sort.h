// heap_sort.h
//
// This implements a heap sort on an array of items of type hedger::S_T.
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

#ifndef HEAP_SORT_H_
#define HEAP_SORT_H_

#include "algo.h"

namespace hedger
{
class HeapSort : public Algo
{
 public:
  HeapSort();
  ~HeapSort();
  int Test(hedger::S_T *arr, size_t size, hedger::S_T range = 0);
  const char *GetName() { return "Heap Sort"; }
 private:
  inline int Parent(int index) { return index >> 1; }
  inline int Left(int index) { return index << 1; }
  inline int Right(int index) { return (index << 1) + 1; }
  void MaxHeapify(int size, int index);
  void BuildMaxHeap(int size);
  void SortRecurse(int size);
  void Sort(hedger::S_T *arr, int size);
  inline void Swap(int index_a, int index_b);
};
}

#endif // HEAP_SORT_H_
