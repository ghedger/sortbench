#ifndef QUICK_SORT_H_
#define QUICK_SORT_H_

#include "algo.h"

namespace hedger
{
class QuickSort : public Algo
{
 public:
  QuickSort();
  ~QuickSort();
  int Test(hedger::S_T *arr, size_t size, hedger::S_T range = 0);
 protected:
  int Partition(hedger::S_T *arr, int start, int end);
  void Sort(hedger::S_T *arr, int start, int end);
  void SortRecurse(hedger::S_T *arr, int start, int end);
  const char *GetName() { return "Quick Sort"; }
 private:
  inline void Swap(hedger::S_T *arr, int index_a, int index_b);
};
}

#endif // QUICK_SORT_H_
