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
    printf("Ahoj Praha, I'm a thread <%s>\n", (const char*) arg);
    return NULL;
}


int main()
{
    pthread_t tid;
    int rc;

    rc = pthread_create(&tid, NULL, hello_eoss, "hello_eoss");
    assert_pthread(rc, "pthread_create");

    rc = pthread_join(tid, NULL);
    assert_pthread(rc, "pthread_join");

    return 0;
}
