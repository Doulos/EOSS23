#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

volatile unsigned int counter = 0;

// write is async-signal safe :)
//
void handler(int signo, siginfo_t* info, void* context)
{
    const char* msg = "\nReset the counter!\n";
    write(STDOUT_FILENO, msg ,sizeof(msg)); 
    counter = 0;
}

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
