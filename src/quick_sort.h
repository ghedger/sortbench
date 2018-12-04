#ifndef QUICK_SORT_H_
#define QUICK_SORT_H_

#include "algo.h"

namespace hedger
{
class QuickSort : public Algo
{
 public:
  QuickSort();
  virtual ~QuickSort();
  int Test(int *arr, std::size_t size);
 protected:
  int FindPartition(hedger::S_T *arr, int start, int end);
  void Sort(hedger::S_T *arr, int start, int end);
 private:
  inline void Swap(hedger::S_T *arr, int index_a, int index_b);
};
}

#endif // QUICK_SORT_H_
