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

#include "btree.h"
#include "stdio.h"

namespace hedger
{

// Constructor
BTree::BTree()
{
  root_ = nullptr;
  size_ = 0;
  maxSize_ = 0;
  q_ = 0;
}

BTree::~BTree()
{
  // TODO: Delete all nodes
  deleteRecursive(root_);
}

void BTree::deleteRecursive(hedger::Node *node)
{
  if (node && node->data) {
    deleteRecursive(node->left);
    deleteRecursive(node->right);
    delete node->data;
    node->data = nullptr;
    delete node;
  }
}


Node *BTree::add(hedger::S_T key, int *depth)
{
  hedger::Node *node = new hedger::Node(key);

  // Is this the first node in the tree?
  if (nullptr == root_) {
    root_ = node;
    q_++;
    *depth = 1;
    return node;
  }

  // Find and set appropriate parent
  Node *currentNode = root_;
  Node *candidateParent = nullptr;
  int currentDepth = 0;
  while (currentNode != nullptr) {
    candidateParent = currentNode;
    if (node->key < currentNode->key) {
      currentNode = currentNode->left;
      currentDepth++;
    } else {
      currentNode = currentNode->right;
      currentDepth++;
    }
  }
  currentDepth++;
  if(depth) {
    *depth = currentDepth;
  }

  node->parent = candidateParent;
  if (node->key < node->parent->key) {
    node->parent->left = node;
  } else {
    node->parent->right = node;
  }
  node->left = nullptr;
  node->right = nullptr;
  changeSize(1);

  q_++;
  return node;
}

// remove
//
// TODO: Implement
//
// Entry:
// Exit:
bool BTree::remove(hedger::S_T key)
{
  bool result = false;
  return result;
}

// find
//
// Find node by key.
//
// Entry: key
// Exit: node
void *BTree::find(hedger::S_T key)
{
  hedger::Node *node = findRecurse(key, root_);
  return node;
}

//
// Helper functions
//

void BTree::changeSize(int delta)
{
  if(size_ + delta > 0 ) {
    size_ += delta;
  }
}

// print
//
// Spit out textual representation of tree
//
// Entry: -
// Exit:  -
void BTree::print(hedger::Node *node)
{
  if (!node) {
    node = root_;
    if (!node) {
      return;
    }
  }
  printf("%08x:%d (p:%08x l:%08x r:%08x)\n", node, node->key, node->parent, node->left, node->right);
  if (node->left) {
    print(node->left);
  }
  if (node->right) {
    print(node->right);
  }
}

hedger::Node *BTree::findRecurse(hedger::S_T key, hedger::Node *node)
{
  if (node) {
    if (node->key == key) {
      return node;
    }
    if (node->key > key) {
      return findRecurse(key, node->left);
    } else if(node->key < key) {
      return findRecurse(key, node->right);
    } else {
      // TODO: Equal case - duplicate keys disallowed
    }
  }
  return nullptr;
}
} // namespace hedger
