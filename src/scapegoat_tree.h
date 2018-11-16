// scapegoat.h
//
// Implements a scapegoat tree derived from BTree.
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

#ifndef SCAPEGOAT_H_
#define SCAPEGOAT_H_

#include "btree.h"

namespace hedger
{

class ScapegoatTree : public hedger::BTree
{
  public:
    ScapegoatTree();
    virtual ~ScapegoatTree();
    hedger::Node *add(hedger::S_T key);

  private:
    static int const log32(int q);
    hedger::Node *findScapegoat(hedger::Node *node);
    bool isBalancedAtNode(hedger::Node *node);
    int sizeOfSubtree(hedger::Node *node);
    int packIntoArray(hedger::Node *node, hedger::Node *rebuildArray[], int i);
    hedger::Node *rebalance(hedger::Node *node);
    hedger::Node *buildBalanced(hedger::Node **rebuildArray, int i, int nodeTot);
};
} // namespace hedger
#endif // #ifndef SCAPEGOAT_H_

