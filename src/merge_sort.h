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

#ifndef MERGE_SORT_H_
#define MERGE_SORT_H_

#include "algo.h"

namespace hedger
{
class MergeSort : public Algo
{
  public:
    MergeSort();
    virtual ~MergeSort();
    int Test(int *arr, std::size_t size);
    void Merge(int *arr, int start, int mid, int end);
    void Sort(int *arr, int start, int end);
};
}

#endif // MERGE_SORT_H_
