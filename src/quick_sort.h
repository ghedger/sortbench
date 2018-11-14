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
    int test(int *arr, std::size_t size);
    int findPartition(hedger::S_T *arr, int start, int end);
    void sort(hedger::S_T *arr, int start, int end);
};
}

#endif // QUICK_SORT_H_
