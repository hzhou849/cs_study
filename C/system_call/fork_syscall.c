/*
 * fork() system call
 * 
 * Used to create a child process. 
 * 
 * Args: NONE
 * 
 * Returns: Process ID
 * 
 * //http://www.csl.mtu.edu/cs4411.ck/www/NOTES/process/fork/create.html
 * 
 * 
 * write() is used instead of printf, bc it is an immediate write to terminal.
 */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#define MAX_COUNT 	200
#define BUF_SIZE 	100


int main(void) 
{
	pid_t pid;
	int i;
	char buf[BUF_SIZE];

	fork();
	pid = getid();		// returns the childs PID
	for (i = 1; i <= MAX_COUNT; i++)
	{
		sprintf(buf, "pid %d, value = %d\n", pid, i);		// writes to buffer
		write(1, buf, strlen(buf));							// write(<fd 1 is stdin>, *buffer, size_t writeSize)
	}
	return 0;
}