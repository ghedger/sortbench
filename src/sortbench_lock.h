// sortbench_lock.h
//
// lock implementation
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

#ifndef _SORTBENCH_LOCK_H_
#define _SORTBENCH_LOCK_H_

#include <sched.h>

namespace hedger {

// Lock
// Simple lock class for acquisition and release of lock
class Lock {
 public:
  Lock() { lock_ = 0; }
  ~Lock() {}
  // Acquire
  inline void Acquire() {
    while (__sync_lock_test_and_set(&lock_, 1));
#if 0
    while (lock_) {
      // Occupado, sister; Force a context switch and wait our turn
      // (TODO: Is this even necessary?)
      sched_yield();
    }
    // Low-level lock on Intel processors
    __sync_lock_test_and_set(&lock_, 1);
#endif
  }
  // Release
  inline void Release() {
    // Low-level release on Intel chips
    #if 1
    lock_ = 0;
    #else
    __sync_lock_release(&lock_);
    #endif
  }
 private:
  volatile int lock_;
};
} // namespace anagram
#endif // #ifndef _SORTBENCH_LOCK_H_

