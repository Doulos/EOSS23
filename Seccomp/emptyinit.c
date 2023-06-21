#include <stdio.h>
#include <unistd.h>

int main(void)
{
	while(1) {
		printf("Am i alive?\n");
		sleep(30);
	}

	return 0;
}
