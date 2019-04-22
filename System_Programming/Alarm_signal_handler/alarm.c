/* Alarm Signal and Signal Handler
 *
 * 
 */



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


void sig_handler(int signum) {
	printf("Alarm signal delivered signum is %d\n", signum);
	system("/bin/ls");
	exit(0);
}

int main() {
	alarm(5);
	signal(SIGALRM, sig_handler);

	for(;;) 	// infinite loop
		sleep(1);

	return 0;
}


