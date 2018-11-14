// btree.h
//
// Implements an unbalanced binary tree.
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

#ifndef BTREE_H_
#define BTREE_H_

#include "algo.h"

namespace hedger
{
struct Node
{
  Node *      l;        // left leg
  Node *      r;        // right leg
  Node *      p;        // parent (could be axed)
  hedger::S_T key;      // key
  void *      data;     // payload / "satellite" data
};


class BTree
{
  public:
  BTree();
  virtual ~BTree();

  bool add(hedger::S_T key);
  bool remove(hedger::S_T key);
  void *find(hedger::S_T key);
};
} // namespace hedger
#endif // #ifndef BTREE_H_

