/* simple program to run as daemon to test systemd seccomp filtering */

#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <syslog.h>

int main(void)
{
    struct utsname name;

    if (uname(&name)) {
        perror("uname failed: ");
        return 1;
    }

    while (1) {
	    syslog(LOG_USER, "Kernel version: %s", name.release); 
	    sleep(30);
    }

    return 0;
}
