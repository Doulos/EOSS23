## Questions & Answers 

This section is a collection of the questions asked during and after the talk.

### What is this `grepai` tool?
It's a joke based on the famous [AI meme](ai_meme.jpg)

### You presented POSIX threads, but threads are available in C11?
That's absolutely true: thread is part of the C11 language (and C++11 for that matter).
Note that thread is an optional feature of the C11 language.
If threads are not supported, the macro **__STDC_NO_THREADS__** is defined.

On Linux, C11 threads are implemented on the top of POSIX threads.
This can be easily seen for instnace in the MUSL source: 
- `src/thread/pthread_create.c`. Look in particular at the **c11** flag
- `src/thread/thrd_create.c`, which implements the **thrd_create** API.

Looking at the C11 thread APIs, it seems relatively straightforward to move from POSIX to C11 thread.
Of course, you might want to verify the behaviour using the table mentioned during the talk.

### priority inheritance mutex (aka. PI-mutex) is not available in glibc/musl.

I'm a bit surpised by this statement. From my understanding, PI-mutex are available in glibc and musl.
However a proper kernel support is required: it should provide the PI futex interface.

I need to dig deeper on this... Stay tuned!

**Further Questions or feedbacks? Contact us!**
