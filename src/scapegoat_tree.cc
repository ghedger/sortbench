// scapegoat.cc
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

#include <math.h>

#include "scapegoat_tree.h"

namespace hedger
{

// Constructor
ScapegoatTree::ScapegoatTree() : BTree::BTree()
{
}

// Destructor
ScapegoatTree::~ScapegoatTree()
{
  // TODO: delete all nodes to eliminate memory leaks
}

// log32
//
// Gets the log-base 3/2 of tree
//
// (source: https://www.sanfoundry.com/cpp-program-implement-scapegoat-tree/)
int const ScapegoatTree::log32(int q)
{
  double const log23 = 2.4663034623764317;
  return (int) ceil(log23 * log(q));
}

// add
//
// Add a node to the tree structure.
//
// Entry:  key of new node
hedger::Node *ScapegoatTree::add(hedger::S_T key)
{
  // Use BTree's regular unbalanced insertion
  int depth;
  hedger::Node *node = BTree::add(key, &depth);

  // Is it time to rebalance?
  int q = log32(q_);
  if (depth > q) {
    // Walk up tree starting at our node.
    hedger::Node *walk = node->parent;
    if (walk) {
      while (3 * sizeOfSubtree(walk) <= 2 * sizeOfSubtree(walk->parent)) {
        walk = walk->parent;
      }
      if (walk->parent) {
        rebalance(walk->parent);
      }
    }
  }

  return node;
}

// findScapegoat
//
// Find a node that meets the log-base-alpha requirement for
// a rebalance root.
//
// Entry:  Start node from which we'll walk up.
// Exit: -
hedger::Node *ScapegoatTree::findScapegoat(hedger::Node *node)
{
  if (node == root_) {
    return nullptr;
  }
}

bool ScapegoatTree::isBalancedAtNode(hedger::Node *node)
{
}

int ScapegoatTree::sizeOfSubtree(hedger::Node *node)
{
  if (!node) {
    return 0;
  }
  return sizeOfSubtree(node->left) + sizeOfSubtree(node->right) + 1;
}

// packIntoArray
//
// Put nodes into a flat array for rebuilding purposes.  We
// recursively call ourselves traversing the tree from the reroot
// base.
//
// Entry:  root node
//        rebuild array of node pointers
//        current array index
int ScapegoatTree::packIntoArray(hedger::Node *node, hedger::Node *rebuildArray[], int i)
{
    if (!node) {
        return i;
    }
    i = packIntoArray(node->left, rebuildArray, i);
    rebuildArray[i++] = node;
    return packIntoArray(node->right, rebuildArray, i);
}

// rebalance
//
// Flatten the tree and rebuild it from the designated root node.
//
// Entry:  root node of subtree to rebuild
// Exit:
hedger::Node *ScapegoatTree::rebalance(hedger::Node *node)
{
  // Allocate temporary array for new flattened tree.
  // This array holds pointers to nodes.
  int nodeTot = sizeOfSubtree(node);
  hedger::Node *parent = node->parent;
  hedger::Node **rebuildArray = new hedger::Node* [nodeTot];
  packIntoArray(node, rebuildArray, 0);

  if (!parent) {
    hedger::Node *root = buildBalanced(rebuildArray, 0, nodeTot);
    root->parent = nullptr;
  } else if (parent->right == node) {
    parent->right = buildBalanced(rebuildArray, 0, nodeTot);
    parent->right->parent = parent;
  } else {
    parent->left = buildBalanced(rebuildArray, 0, nodeTot);
    parent->left->parent = parent;
  }
}

// buildBalanced
//
//
hedger::Node *ScapegoatTree::buildBalanced(hedger::Node **rebuildArray, int i, int nodeTot)
{
  if (!nodeTot) {
    return NULL;
  }

  int m = nodeTot / 2;
  rebuildArray[i + m]->left = buildBalanced(rebuildArray, i, m);
  if (rebuildArray[i + m]->left != nullptr) {
    rebuildArray[i + m]->left->parent = rebuildArray[i + m];
  }
  rebuildArray[i + m]->right = buildBalanced(rebuildArray, i + m + 1, nodeTot - m - 1);

  if (rebuildArray[i + m]->right != nullptr) {
    rebuildArray[i + m]->right->parent = rebuildArray[i + m];
  }

  return rebuildArray[i + m];
}

#if 0
def findScapegoat(self, node):
        if node == self.root:
            return None
        while self.isBalancedAtNode(node) == True:
            if node == self.root:
                return None
            node = node.parent
        return node

    def isBalancedAtNode(self, node):
        if abs(self.sizeOfSubtree(node.left) - self.sizeOfSubtree(node.right)) <= 1:
            return True
        return False

    def sizeOfSubtree(self, node):
        if node == None:
            return 0
        return 1 + self.sizeOfSubtree(node.left) + self.sizeOfSubtree(node.right)

    def rebalance(self, root):
        def flatten(node, nodes):
            if node == None:
                return
            flatten(node.left, nodes)
            nodes.append(node)
            flatten(node.right, nodes)

        def buildTreeFromSortedList(nodes, start, end):
            if start > end:
                return None
            mid = int(math.ceil(start + (end - start) / 2.0))
            node = Node(nodes[mid].key)
            node.left = buildTreeFromSortedList(nodes, start, mid-1)
            node.right = buildTreeFromSortedList(nodes, mid+1, end)
            return node

        nodes = []
        flatten(root, nodes)
        return buildTreeFromSortedList(nodes, 0, len(nodes)-1)
#endif





} // namespace hedger
