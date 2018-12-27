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

// C headers
#include <stdio.h>
#include <math.h>
#include <string.h>

// C++ headers
#include <iostream>
#include <cmath>
#include <set>
#include <vector>
#include <chrono>

// Project-specific
#include "sortbench_common.h"
#include "algo.h"
#include "merge_sort.h"
#include "merge_sort_multicore.h"
#include "quick_sort.h"
#include "quick_sort_randomized.h"
#include "counting_sort.h"
#include "heap_sort.h"
#include "insertion_sort.h"

// This global flag determines whether we print out the array.
// Used for cursory validation of new sorting algorithms.
static bool verbose = false;
static bool fast_only = false;  // only include fast algorithms
// PrintLicense
void PrintLicense()
{
  using namespace std;
  cout << "Sortbench is free software: you can redistribute it and/or modify" << endl;
  cout << "it under the terms of the GNU General Public License as published by" << endl;
  cout << "the Free Software Foundation, either version 3 of the License, or" << endl;
  cout << "(at your option) any later version." << endl;
  cout << "Sortbench is distributed in the hope that it will be useful," << endl;
  cout << "but WITHOUT ANY WARRANTY; without even the implied warranty of" << endl;
  cout << "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the" << endl;
  cout << "GNU General Public License for more details." << endl;
  cout << "You should have received a copy of the GNU General Public License" << endl;
  cout << "along with sortbench.  If not, see <https://www.gnu.org/licenses/>." << endl;
}

// PrintUsage
//
// Present the user with the usage instructions
void PrintUsage()
{
  using namespace std;
  cout << "sortbench" << endl;
  cout << "Copyright (C) 2018 Greg Hedger" << endl;
  PrintLicense();
  cout << "Usage:" << endl;
  cout << "\tsortbench [-v] [-f] <array_size> <iteration_total>" << endl;
  cout << "Flags:" << endl;
  cout << "\t-v - verbose: print full array before and after each sort" << endl;
  cout << "\t-f - fast: exclude O(n^2) alogrithms" << endl;
  cout << "\t-s - include already-sorted array for testing" << endl;
}

// printArray
//
// Prints n values of an array
//
// Entry: pointer
//        number of items to print
// Exit:  -
void PrintArray(const hedger::S_T *array, size_t n)
{
  const int kColumnCount = 16;
  int column_count = kColumnCount;
  for (size_t i = 0; i < n; i++) {
    printf("%04x  ", array[i]);
    if (!--column_count) {
      column_count = kColumnCount;
      printf("\n");
    }
  }
  if (column_count < kColumnCount)
    printf("\n");
}

// AllocArray
// Entry: size of array in elements
// Exit:  pointer to array, or nullptr == error
hedger::S_T * AllocArray(size_t size)
{
  // Allocate the array
  hedger::S_T *array = new hedger::S_T[ size ];
  if (!array) {
    // TODO: SEND TO LOGGER
    printf(" %s: Allocation error", __FUNCTION__);
    return nullptr;
  }
  return array;
}

// FreeArray
// Entry: pointer to array
void FreeArray(hedger::S_T *array)
{
  if (array) {
    delete array;
  }
}

// CreateRandomDataSet
// Fills an array with pseudo-random data, with duplicates
// Entry: array
//        size in elements
//        value range (optional)
void CreateRandomDataSet(hedger::S_T *array, size_t size, size_t range = 0)
{
  size_t index = 0;
  hedger::S_T value = 0;
  if (!range) {
    range = size;
  }
  // Generate array of scrambled unsorted non-unique data in the array
  while (index < size) {
    value = (hedger::S_T) rand() % range;
    array[index] = value;
    ++index;
  }
}

// CreateSortedDataSet
// Fills an array with unique ascending-order data
// Entry: array
//        size in elements
void CreateSortedDataSet(hedger::S_T *array, size_t size)
{
  size_t index = 0;
  hedger::S_T value = 0;
  // Generate array of scrambled unsorted non-unique data in the array
  while (index < size) {
    array[index] = value;
    ++index;
    ++value;
  }
}
// CreateUniqueDataSet
// Fills an array with unique pseudo-random values.
// Entry: array
//        size in elements
void CreateUniqueDataSet(hedger::S_T *array, size_t size)
{
  // In-situ STL map<> for quick lookup of already-used random values
  std::set<hedger::S_T> occupancy;

  size_t index = 0;
  hedger::S_T value = 0;
  // Generate array of scrambled unsorted but unique data in the array
  while (index < size) {
    // Get random number; if used, go fish again...
    do {
      value = rand() % size;
      //std::cout << value << std::endl;
    } while (occupancy.find(value) != occupancy.end());
    occupancy.insert(value);
    array[index] = value;
    ++index;
  }
}

// test
//
// Run the test on the Algo-derived search algorithm object
//
// Entry: pointer to algorithm object
//        pointer to array
//        size of array
int Test(hedger::Algo& o, hedger::S_T *arr, size_t size)
{
  int result = o.Test(arr, size, size);
  return result;
}

// ReportTiming
// Calculate and report mean and standard deviation of timing.
// Entry: vector of times
//        name of algorithm
// TODO: Move this to its own utility class
void ReportTiming(std::vector<double>& v, int iteration_tot, const char *name)
{
    // Calculate average (mu)
    double mu, sigma;
    double accum = 0.0;
    for (auto i : v) {
      accum = accum + i;
    }
    mu = (double) accum / (double) iteration_tot;
    double time_tot = accum;

    // Calculate std deviation (sigma)
    accum = 0.0;
    for (auto i : v) {
      accum += pow(( (double) i - mu), 2);
    }
    sigma = sqrt(accum / iteration_tot);

    // Print report
    std::cout << COUT_YELLOW << name << ":" << COUT_NORMAL << std::endl;
    std::cout << "IT: " << iteration_tot << "\t";
    std::cout << CHAR_MU << ":" << mu << " ms" << "\t";
    std::cout << CHAR_SIGMA << ":" << sigma << " ms\t";
    std::cout << "TIME TOTAL: " << time_tot << " ms" << std::endl;
}

// RunTest
// Entry: reference to timing vector
//        reference to algorithm
//        pointer to array buffer
//        size of array buffer in elements
//        # of iterations for which to test
void RunTest(std::vector<double>& time_arr,
  hedger::Algo& algorithm,
  hedger::S_T *array,
  const int array_size,
  const int iterations,
  const bool unique
)
{
  using namespace std;
  using FpMilliseconds =
        chrono::duration<float, chrono::milliseconds::period>;
  auto iteration_count = iterations;
  while (iteration_count) {
    --iteration_count;
      if (verbose) {
        cout << algorithm.GetName() << " BEFORE:" << endl;
        PrintArray(array, array_size);
      }
      auto start = chrono::high_resolution_clock::now(); // mark start time
      Test( algorithm, array, array_size ); // Do work
      auto stop = chrono::high_resolution_clock::now();  // mark end time
      auto ms = FpMilliseconds(stop - start); // get elapsed time in ms
      double ms_float = ms.count(); // get as a float
      time_arr.push_back(ms_float); // save in our timing array
      if (verbose) {
        cout << algorithm.GetName() << " AFTER: " << endl;
        PrintArray(array, array_size);
      }
  }
}

// main
int main(int argc, const char **argv)
{
  using namespace hedger;
  static const int kAlgoTot = 6;
  int result = 0;

  std::cout.precision(5);        // sets the precision and fixedness
  std::cout.setf(std::ios::fixed);

  Algo *algo_arr[kAlgoTot];

  // TODO: Replace with Registry pattern
  // Seed random number generator (use seconds since epoch)
  srand((unsigned int) time(NULL));

  // Gather user parameters: array_size, iteration_tot
  size_t array_size;
  int iteration_tot;
  array_size = iteration_tot = 0;

  if (argc < 3) {
    PrintUsage();
    return -1;
  }

  int arg_idx = 1;
  bool include_already_sorted = false;
  while ('-' == argv[arg_idx][0])
  {
    switch (argv[arg_idx][1]) {
      case 'v':
        verbose = true;
        break;
      case 'f':
        fast_only = true;
        break;
       case 's':
        include_already_sorted = true;
        break;
      default:
        PrintUsage();
        return -1;
    }
    ++arg_idx;
  }

  int algo_total = 0;
  algo_arr[algo_total++] = new MergeSort();
  algo_arr[algo_total++] = new MergeSortMultiCore();
  algo_arr[algo_total++] = new QuickSort();
  algo_arr[algo_total++] = new QuickSortRandomized();
  algo_arr[algo_total++] = new CountingSort();
  algo_arr[algo_total++] = new HeapSort();
  if (!fast_only) {
    algo_arr[algo_total++] = new InsertionSort();
  }


  if (!argv[arg_idx] || !argv[arg_idx + 1]) {
    PrintUsage();
    return -1;
  }

  sscanf(argv[arg_idx++], "%d", (int *) &array_size);
  sscanf(argv[arg_idx], "%d", &iteration_tot);

  // Validate params
  if (!array_size || !iteration_tot) {
    PrintUsage();
    return -1;
  }

  // Timing variables for statistical analysis
  std::vector<double> time_arr[kAlgoTot];
  // Allocate our array
  S_T *array = AllocArray(array_size);
  S_T *master_array = AllocArray(array_size);
  if (array) {
    // This runs the sorting tests against a unique data set.
    std::cout << "(Generating unique array)" << std::endl;
    std::cout << COUT_AQUA << "UNIQUE:";
    CreateUniqueDataSet(master_array, array_size);
    std::cout << COUT_NORMAL << std::endl;
    for (auto i = 0; i < algo_total; ++i) {
      memcpy(array, master_array, array_size * sizeof(hedger::S_T));
      RunTest(
        time_arr[i],
        *algo_arr[i],
        array,
        array_size,
        iteration_tot,
        true
      );
      ReportTiming(time_arr[i], iteration_tot, algo_arr[i]->GetName());
    }
    if (include_already_sorted) {
      // This runs the sorts on already-sorted data.
      std::cout << COUT_AQUA << "ALREADY-SORTED:";
      CreateSortedDataSet(master_array, array_size);
      std::cout << COUT_NORMAL << std::endl;
      for (auto i = 0; i < algo_total; ++i) {
        memcpy(array, master_array, array_size * sizeof(hedger::S_T));
        RunTest(
          time_arr[i],
          *algo_arr[i],
          array,
          array_size,
          iteration_tot,
          true
        );
        ReportTiming(time_arr[i], iteration_tot, algo_arr[i]->GetName());
      }
    }


    // This runs the sorting tests against data sets containing duplicates.
    std::cout << COUT_AQUA << "NONUNIQUE:" << COUT_NORMAL << std::endl;
    CreateRandomDataSet(master_array, array_size, array_size / 2);
    for (auto i = 0; i < algo_total; ++i) {
      memcpy(array, master_array, array_size * sizeof(hedger::S_T));
      RunTest(
        time_arr[i],
        *algo_arr[i],
        array,
        array_size,
        iteration_tot,
        false
      );
      ReportTiming(time_arr[i], iteration_tot, algo_arr[i]->GetName());
    }
  } else {
    // TODO: SEND TO LOGGER
    printf("Failed to allocate data set array.\n");
    result = -1;
  }

  // Clean up
  if (nullptr != array) {
    delete master_array;
    delete array;
    array = nullptr;
  }

  for (auto i = 0; i < algo_total; ++i) {
    delete algo_arr[i];
  }

  return result;
}
