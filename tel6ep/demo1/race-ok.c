// This program shows a possible solution for race.c
//
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
void* hello_eoss(void *arg) 
{
    printf("Ahoj Prag, I'm thread <%d>\n", *((int*) arg));
    return NULL;
}

const int NTHREADS = 5;

int main()
{
    pthread_t tid[NTHREADS];
    int args[NTHREADS]; // one arg per thread
    int rc;

    // start the thread pool
    //
    // one way to solve the race condition when passing argument
    // is to have one dedicated argument per thread.
    //
    // As we're passing a pointer, we should ensure that the
    // pointee is still valid when the thread starts.
    // 
    for (int n=0; n<NTHREADS; ++n) {
        args[n] = n;
        rc = pthread_create(&tid[n], NULL, hello_eoss, &args[n]);
        assert_pthread(rc, "pthread_create");
    }

    for (int n=0; n<NTHREADS; ++n) {
        rc = pthread_join(tid[n], NULL);
        assert_pthread(rc, "pthread_join");
    }

    return 0;
}
