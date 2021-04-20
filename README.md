# Summary

Sortbench is a GNU/posix command line test bench for analyzing various sorting algorithms against integer arrays.  Two flavors are tested: arrays where each value is unique from all other values, and arrays with non-unique duplicated values.  It offers averaging of multiple successive iterations of a given sort algorithm, the ability to filter out known innefficient methods (e.g. bubble sort).  Through this, insight can be gained on the best algorithm to select for a given application with a given set of constraints.  There are "better" and "worse" algorithms, but no one-size-fits-all for everything -- one reason sorting has occupied such a prominent seat in computer science.

# Options
  -v - verbose: print full array before and after each sort (useful for debugging)
	-f - fast: exclude O(n^2) alogrithms
	-s - include already-sorted array for testing
	-m - exclude memory-expensive algorithms like counting sort

# Params

  * array size
  * # of full sort iterations

# Output
T: 1000	μ:1.6351 ms	σ:0.0708 ms	Τ:1635.1243 ms	MRD: 32

  * Average time per iteration (μ)
  * Standard time deviation for all iterations (σ)
  * Total aggregate time for all iterations (T)
  * Maximum recursion depth (MRD, for recursive algorithms only)

= Algoritms Compared =

  * Quick Sort
  * Quick Sort w/randomized partition
  * Counting Sort
  * Radix Sort
  * Merge Sort
  * Merge Sort Multicore
  * Heap Sort
  * Insertion Sort

= Future Improvements =

I would like to track the memory usage.  For example, Counting Sort is the obvious winner in situations where the domain range of the data is known (e.g. integers between 0 and some known upper limit), but has high memory consumption.  This memory usage must account for stack space -- recursive algorithms are not free; instead more stack memory is used in lieu of heap memory.
