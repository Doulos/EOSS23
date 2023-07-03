#define _GNU_SOURCE   // use GNU extension pthread_getattr_np 
#include <pthread.h>
#include <stdlib.h>  // exit()
#include <stdio.h>   // fprintf()
#include <string.h>  // strerror()
#include <unistd.h>

#define KB 1024
#define ALLOC_SZ 1024*KB


void assert_pthread(int rc, const char* func_name)
{
    if (rc!=0) {
        fprintf(stderr,"%s() = %d: %s",
                func_name, rc, strerror(rc));
        exit(EXIT_FAILURE);
    }
}


void
print_stack_info(pthread_t* tid) 
{
    int rc;
    pthread_attr_t attr;
    void*  stackaddr;
    size_t stacksize, guardsize;

    // get the thread attribute used to create tid
    // here we want to introspect the stack created by the
    // C runtime library. 
    // 
    // If we want to change the default thread creation
    // attribute, we'd normally use:
    // - pthread_attr_init(&attr) to create the default values
    // - pthread_attr_set* to change the values of interested.
    //
    // pthread*_np are non standard POSIX extension 
    // available both in glibc and musl
    //
    rc = pthread_getattr_np(*tid, &attr);
    assert_pthread(rc, "pthread_getattr_np");

    // query stack address, size and guard's size
    // 
    pthread_attr_getstack(&attr, &stackaddr, &stacksize);
    assert_pthread(rc, "pthread_attr_getstack");
    pthread_attr_getguardsize(&attr, &guardsize);
    assert_pthread(rc, "pthread_attr_getguardsize");

    // print stack information. 
    // it assumes that the stack growths downward
    // also print the value of tid, interpreted as a pointer
    //
    printf("stack: addr=%p->%p, size= %zd KiB\n", 
            stackaddr+stacksize, stackaddr, stacksize/KB);
    printf("tid  : addr=%p (value intrepreted as pointer)\n", *tid);
    printf("guard: size=%zd KiB\n", guardsize/KB);
}


void* stack_overflow(void *arg)
{
    char table[ALLOC_SZ];

    // pause before starting the whole experiment
    // user should type enter to continue the test
    if (arg==NULL) {
        char c = getchar();
    }

    printf("table= %p \n", table);
    stack_overflow(table);
}


int main()
{
    pthread_t tid;
    int rc;

    rc = pthread_create(&tid, NULL, stack_overflow, NULL);
    assert_pthread(rc, "pthread_create");

    print_stack_info(&tid);

    pthread_join(tid, NULL);
    return 0;
}
