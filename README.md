# Summary
Sortbench is a GNU/posix command line test bench for analyzing various sorting algorithms against integer arrays.  Two flavors are tested: arrays where each value is unique from all other values, and arrays with non-unique duplicated values.  It offers averaging of multiple successive iterations of a given sort algorithm, the ability to filter out known innefficient methods (e.g. bubble sort).  Through this, insight can be gained on the best algorithm to select for a given application with a given set of constraints.  

# Options
  -v - verbose: print full array before and after each sort (useful for debugging)
  -f - fast: exclude O(n^2) alogrithms
  -s - include already-sorted array for testing
  -m - exclude memory-expensive algorithms like counting sort

# Params
  * array size
  * total number of rounds of full sort operations to perform for each algorithm

# Output
  * Average time per iteration (μ)
  * Standard time deviation for all iterations (σ)
  * Total aggregate time for all iterations (T)
  * Maximum recursion depth (MRD, for recursive algorithms only)

# Algorithms
  * Quick Sort
  * Quick Sort w/randomized partition
  * Counting Sort
  * Radix Sort
  * Merge Sort
  * Merge Sort Multicore
  * Heap Sort
  * Insertion Sort

# Conclusion
There are "better" and "worse" algorithms, but no one-size-fits-all for everything -- one reason sorting has occupied such a prominent seat in computer science.  For example, Heap Sort Multicore is a good general-purpose nonstable sort if the list to be sorted is large, whereas of sorting a smaller list many times Heap Sort single-threaded would be preferred on account of the thread creation overhead.  One way to improve this for Heap Sort Multicore would be thread pooling.

By using the -s flag, you can immediately see the Achilles' Heel of the much-venerated quick sort without R.C. Singleton's randomized partition optimation -- an extremely narrow case where the normally fast algorithm drops from O (n log n) to a lethargic n^2 - if the data is already sorted or has only a few items out of order and not by much, the much-maligned Bubble Sort outperforms Quick Sort by several orders of magnitude.

# Future Improvements
It would prove useful to track the memory usage.  For example, Counting Sort is the obvious winner in situations where the domain range of the data is known (e.g. integers between 0 and some known upper limit), but brings the disadvantage of high memory consumption.  

This memory usage accounting must extend to stack space: recursive algorithms are not free; instead, more stack memory is used in lieu of heap memory.  This is not necessarily a bad thing as allocating/de-allocating from the stack requires very few CPU cycles (basically, a subtract on the stack register for the frame size, and subsequent add for de-allocation) compared to heap allocation and de-allocation.

Heap Sort Multicore thread pooling: creating the various threads in advance and have them idle and waiting for work to do rather than creating them in situ at the time needed.  For this algorithm, there is a substantial penalty for using ALL of the available cores vs. using 2 fewer (assuming more than 2 cores); I have been unable to figure out why this is.

Tim Sort, American Flag Sort, and other hybrid algorithms ought to be added to the suite.
