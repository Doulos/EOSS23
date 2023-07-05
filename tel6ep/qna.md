## Questions & Answers 

This section is a collection of the questions asked during and after the talk.

### What is this `grepai` tool?
It's a joke based on the famous [AI meme](ai_meme.jpg)

### threads.h is included in C since C11. Could we not use these in Embedded Linux?
Yes absolutely!

Threads are part of the C11 language (and C++11 for that matter).
Note this is an optional feature of the C11 language.  The macro
**__STDC_NO_THREADS__** is defined, if this feature isn't available.

On Linux, C11 threads are implemented on the top of POSIX threads.
This can be easily seen for instance in the MUSL source:
- `src/thread/pthread_create.c`. Look in particular at the **c11** flag
- `src/thread/thrd_create.c`, which implements the **thrd_create** API.

Looking at the C11 thread APIs, it seems relatively straightforward to move
from POSIX to C11 thread. Of course, you might want to verify the behaviour
using the table mentioned during the talk.

### priority inheritance mutex (aka. PI-mutex) is not available in glibc/musl.
I'm a bit surpised by this statement. From my understanding, PI-mutex are available in both glibc and musl. However a proper kernel support is required:
it should provide the PI futex interface.

I need to dig deeper on this... Stay tuned!

### Further Questions or feedbacks? Contact us!
