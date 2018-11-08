#ifndef MERGE_SORT_H_
#define MERGE_SORT_H_

#include "algo.h"

namespace hedger
{
class MergeSort : public Algo
{
  public:
    MergeSort();
    virtual ~MergeSort();
    int test(int *arr, std::size_t size);
    void merge(int *arr, int start, int mid, int end);
    void sort(int *arr, int start, int end);
};
}

#endif // MERGE_SORT_H_
