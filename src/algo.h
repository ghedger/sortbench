#ifndef ALGO_H_
#define ALGO_H_

#include <cstddef>

namespace hedger {

typedef int S_T;

class Algo
{
  public:
    virtual int test(int *t, std::size_t size) = 0;
};
}

#endif // ALGO_H_
