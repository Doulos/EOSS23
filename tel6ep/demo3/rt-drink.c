// This programs shows how a deadlock can occur, even if we're not
// using threads at all. 
//
// To trigger the bug, press Ctrl-C continuously. Depending on the target
// machine, it might be difficult to get the "right timing" to trigger 
// the bug. In this case, you might want to "hammer" the program with 
// SIGINT from another shell using a command similar to:
//
// $ while (true); do kill -s INT `pidof rt-drink`; done 

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

volatile unsigned int counter = 0;

// SIGINT handler to reset the counter
//
// This code has a bug: printf() is not async-signal-safe =
// not safe to be used in signal handler. Signal safety is 
// discussed in: man 7 signal-safety
//
// printf() uses internally some mutex to protect the file
// structure. This make printf() "thread-safe", but not 
// reentrant.
//
// Indeed, if the timing is unlucly, the signal SIGINT will
// interrupt printf() after it locked the mutex and before 
// it releases it. When printf() is called in the signal handler,
// printf() is re-entered and the mutex is locked a second time.
// This causes the deadlock.
//
// the man3 pages have a section called "attributes" that lists 
// the safety garantee of the system API.
// 
void handler(int signo, siginfo_t* info, void* context)
{
    printf("\nReset the counter!\n");
    counter = 0;
}


// set the signal handler for Ctr-C (SIGINT) using sigaction.
//
// here we're using SA_SIGINFO, which gives additional information to the 
// signal handler (parameter siginfo_t and context) 
// 
// we're not making any use of this parameters here. This extra signal
// information are often useful in the context of safety critical software.
//
void set_signal_handler()
{
    struct sigaction act;

    act.sa_flags = SA_SIGINFO;
    act.sa_sigaction = &handler;

    if (sigaction(SIGINT, &act, NULL) == -1)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
}

// our real-time monitor for breverage
// it's just version v0.01 ;)
//
void rt_monitor()
{
    while (1) {
        printf("world consumption: %d bottles of beer\r", counter);
        counter++;
    }
}


int main()
{
    set_signal_handler();
    rt_monitor();

    return 0;
}
