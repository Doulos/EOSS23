## Errata

The locking mechanism used by printf/stdio is best seen by looking at the
implementation of `__lockfile()`. During the talk, I opened the header file 
instead of the c file.
```c
// file:  src/stdio/__lockfile.c

#include "stdio_impl.h"
#include "pthread_impl.h"

int __lockfile(FILE *f)
{
	int owner = f->lock, tid = __pthread_self()->tid;
	if ((owner & ~MAYBE_WAITERS) == tid)
		return 0;
	owner = a_cas(&f->lock, 0, tid);
	if (!owner) return 1;
	while ((owner = a_cas(&f->lock, 0, tid|MAYBE_WAITERS))) {
		if ((owner & MAYBE_WAITERS) ||
		    a_cas(&f->lock, owner, owner|MAYBE_WAITERS)==owner)
			__futexwait(&f->lock, owner|MAYBE_WAITERS, 1);
	}
	return 1;
}

void __unlockfile(FILE *f)
{
	if (a_swap(&f->lock, 0) & MAYBE_WAITERS)
		__wake(&f->lock, 1, 1);
}
```

The above code gives a hit that it is "thread related" with `pthread_self()`. 
Here the lock isn't using a pthread mutex, but instead uses the underlying 
low level implementation directly:
- an atomic-compare-and-swap to check if the lock is already taken,
- if so, call the futex system call to wait until the lock is released.

