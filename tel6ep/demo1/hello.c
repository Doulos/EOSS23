#include <pthread.h> 
#include <string.h>  // strerror()
#include <stdio.h>   // printf()
#include <stdlib.h>  // exit()

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
    if (rc!=0) {
        fprintf(stderr,"pthread_create() = %d: %s",
                rc, strerror(rc));
        exit(EXIT_FAILURE);
    }

    return 0;
}
