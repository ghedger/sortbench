#include <stdio.h>

#include <cstddef>

#include "merge_sort.h"

namespace hedger {

MergeSort::MergeSort() {
};

MergeSort::~MergeSort() {
}

int MergeSort::test(int *array, std::size_t size)
{
  int result = 0;

  sort( array, 0, size - 1 );

  return result;
}

//
// Class-specific Implementation
//

// merge
// Merge two subarrays.  Typically called by the mergesort() function.
// Entry: start index
//        middle index
//        end index
// Exit:  -
void MergeSort::merge(int *arr, int start, int mid, int end)
{
  int * tmp_arr = NULL;
  int i = 0;
  int l1 = start;
  int r1 = mid;
  int l2 = mid + 1;
  int r2 = end;

  tmp_arr = new int[ end - start + 1 ];

  while((l1 <= r1) && (l2 <= r2))
  {
    if(arr[l1] < arr[l2])
      tmp_arr[i++] = arr[l1++];
    else
      tmp_arr[i++] = arr[l2++];
  }

  while(l1 <= r1)
    tmp_arr[i++] = arr[l1++];
  while(l2 <= r2)
    tmp_arr[i++] = arr[l2++];

  for(i = start; i <= end; i++) {
    arr[i] = tmp_arr[i - start];
  }

  delete tmp_arr;
}

void MergeSort::sort(int *arr, int start, int end)
{
  int mid = 0;

  if(start < end)
  {
    mid = (start + end) / 2;
    sort(arr, start, mid);
    sort(arr, mid+1, end);

    // printf( " merge: %d %d %d\n", start, mid, end );
    merge(arr, start, mid, end);
  }
}


} // namespace hedger
