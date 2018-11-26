// sortbench.cc
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

#include <stdio.h>
#include <math.h>

#include <map>
#include "algo.h"
#include "merge_sort.h"
#include "quick_sort.h"
#include "btree.h"
#include "scapegoat_tree.h"

// printUsage
//
// Present the user with the usage instructions
void printUsage()
{
  printf("sortbench\n" );
  printf("Usage:\n" );
  printf("\tsortbench <array_size> <array_total> <thread_total>\n");
}

// printArray
//
// Prints n values of an array
//
// Entry: pointer
//        number of items to print
// Exit:  -
void printArray(const hedger::S_T *array, size_t n)
{
  for(size_t i = 0; i < n; i++) {
    printf("%04x\t", array[i]);
  }
  printf("\n");
}

// createDataSet
//
// Allocates and fills an array with unique pseudo-random values.
//
// Entry: size
// Exit:  pointer to array
hedger::S_T * createUniqueDataSet(size_t size)
{
  // Allocate the array
  hedger::S_T *array = new hedger::S_T[ size ];
  if (!array) {
    // TODO: SEND TO LOGGER
    printf(" %s: Allocation error", __FUNCTION__);
    return nullptr;
  }

  // In-situ STL map<> for quick lookup of already-used random values
  std::map<size_t, hedger::S_T> occupancy;

  size_t index = 0;
  hedger::S_T value = 0;
  // Generate array of scrambled unsorted but unique data in the array
  while(index < size) {
    // Get random number; if used, go fish again...
    do {
      value = rand() % size;
    } while (occupancy.find(value) != occupancy.end());
    occupancy[value] = 1;
    array[index] = value;
    ++index;
  }

  return array;
}

// test
//
// Run the test on the Algo-derived search algorithm object
//
// Entry: pointer to algorithm object
//        pointer to array
//        size of array
int test(hedger::Algo *o, hedger::S_T *arr, size_t size)
{
  int result = o->test(arr, size);
  return result;
}

// testBTree()
//
// Test a btree
//
// Entry: -
// Exit:  -
void testBtree()
{
  hedger::ScapegoatTree btree;

  size_t array_size = 16384;
  hedger::S_T *array = createUniqueDataSet( array_size );

  if (!array) {
    // TODO: LOG ERROR
    return;
  }

  for (size_t i = 0; i < array_size; i++) {
    btree.add(array[i]);
  }

  btree.print();

  delete array;
  return;
}

int main(int argc, const char **argv)
{
  int result = 0;

  testBtree();

#if 0
  hedger::MergeSort *mergeSort = new hedger::MergeSort();
  hedger::QuickSort *quickSort = new hedger::QuickSort();

  // Gather user parameters: array_size, array_tot, thread_tot
  if (argc < 4) {
    printUsage();
    return -1;
  }

  size_t array_size;
  int array_tot, thread_tot;
  array_size = array_tot = thread_tot = 0;

  sscanf(argv[1], "%d", (int *) &array_size);
  sscanf(argv[2], "%d", &array_tot);
  sscanf(argv[3], "%d", &thread_tot);

  // Validate params
  if (!array_size || !array_tot || !thread_tot) {
    printUsage();
    return -1;
  }

  // Create the unique unsorted data set
  hedger::S_T *array = createUniqueDataSet( array_size );

  if (array) {
    printf( "BEFORE:\n" );
    printArray(array, array_size);

    //test( mergeSort, array, array_size );
    test( quickSort, array, array_size );

    printf( "AFTER:\n" );
    printArray(array, array_size);
  } else {
    // TODO: SEND TO LOGGER
    printf("Failed to allocate data set array.\n");
    result = -1;
  }

  // Clean up
  if (nullptr != array) {
    delete array;
    array = nullptr;
  }

  if (nullptr != mergeSort) {
    delete mergeSort;
    mergeSort = nullptr;
  }

  if (nullptr != quickSort) {
    delete quickSort;
    quickSort = nullptr;
  }
#endif

  return result;
}
