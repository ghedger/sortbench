// merge_sort.h
//
// Merge sort implementation class header.
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

#ifndef MERGE_SORT_MULTICORE_H_
#define MERGE_SORT_MULTICORE_H_

#include "algo.h"
#include "sortbench_lock.h"

namespace hedger
{
#define BLOCKMAX 12
// MergeSortMultiCore
// Implementation of high-performance multi-core merge sort
class MergeSortMultiCore : public Algo
{
 public:
  MergeSortMultiCore();
  virtual ~MergeSortMultiCore();
  int Test(hedger::S_T *arr, size_t size, hedger::S_T range = 0);
  const char *GetName() { return "Merge Sort Multi-Core"; }
  void Merge(int start, int mid, int end);
  static void *SortRecurse(void *params);
 private:
  static int GetThreadTot() { return thread_tot_; }
  static void SetThreadTot(int thread_tot) { thread_tot_ = thread_tot; }
  void Sort(hedger::S_T *arr, int size);
  // Block stack stuff
  static bool InitAlloc(int size);
  static void ShutdownAlloc();
  // Member variables
  static hedger::Lock *merge_lock_;
  static volatile int thread_tot_;
  static int kThreadMax;
};

// MergeSortMultiParams
// Parameter structure for sorting threads
struct MergeSortMultiParams {
  hedger::S_T *arr;
  int start;
  int end;
  hedger::MergeSortMultiCore *merge_sort;
};


}

#endif // MERGE_SORT_MULTICORE_H_
