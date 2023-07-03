// This program shows a race condition when passing argument
// to the thread's start routine

#include <pthread.h> 
#include <string.h>  // strerror()
#include <stdio.h>   // printf()
#include <stdlib.h>  // exit()


// simplify pthread error checking
// another common technique is to wrap the pthread* call 
//
void assert_pthread(int rc, const char* func_name)
{
    if (rc!=0) {
        fprintf(stderr,"%s() = %d: %s",
                func_name, rc, strerror(rc));
        exit(EXIT_FAILURE);
    }
}


// thread's start routine
//
// thread creation and start is done in one step.
// unless we use some synchronization mechanism, we cannot make
// any assumption when the thread will be running on the CPU
//
void* hello_eoss(void *arg) 
{
    printf("Ahoj Prag, I'm thread <%d>\n", *((int*) arg));
    return NULL;
}

const int NTHREADS = 5;

int main()
{
    pthread_t tid[NTHREADS];
    int rc;

    // Start the thread's pool.
    //
    // There is a race condition here, because when the thread starts,
    // the value for n have likely moved.
    //
    // (The loop might even be finished when the thread starts,
    // so we'll see n=5 in all threads)
    //
    for (int n=0; n<NTHREADS; ++n) {
        rc = pthread_create(&tid[n], NULL, hello_eoss, &n);
        assert_pthread(rc, "pthread_create");
    }

    for (int n=0; n<NTHREADS; ++n) {
        rc = pthread_join(tid[n], NULL);
        assert_pthread(rc, "pthread_join");
    }

    return 0;
}
