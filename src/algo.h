// algo.h
//
// Parent class for algorithms requiring analysis.
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

#ifndef ALGO_H_
#define ALGO_H_

#include <cstddef>

namespace hedger {

typedef int S_T;

// Algo is an ancestor class for any algorithm, and is to be used
// for maintaining relevant statistics on the algorithm (run time, mean, std deviation, etc)
class Algo
{
 public:
  Algo() { max_recurse_depth_ = 0; max_recurse_depth_hwm_ = 0; }
  virtual ~Algo() {};
  virtual int Test(hedger::S_T *t, size_t size, hedger::S_T range = 0) = 0;
  virtual const char *GetName() = 0;
  int GetMaxRecurseDepth() { return max_recurse_depth_hwm_; }
  void ResetMaxRecurseDepth() {
    max_recurse_depth_hwm_ = max_recurse_depth_ = 0;
  }

 protected:
  virtual void IncMaxRecurseDepth() {
    ++max_recurse_depth_;
    if (max_recurse_depth_hwm_ < max_recurse_depth_)
      max_recurse_depth_hwm_ = max_recurse_depth_;
  }
  virtual void DecMaxRecurseDepth() { --max_recurse_depth_; }
  volatile int max_recurse_depth_;
  volatile int max_recurse_depth_hwm_;
  hedger::S_T *arr_;
};
}

#endif // ALGO_H_
