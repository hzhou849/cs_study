/*
 * fork() system call
 * 
 * Used to create a child process. 
 * 
 * Args: NONE
 * 
 * Returns: Process ID
 * 
 * http://www.csl.mtu.edu/cs4411.ck/www/NOTES/process/fork/create.html
 * 
 * 
 * write() is used instead of printf, bc it is an immediate write to terminal.
 */

#include <sys/types.h>
#include <stdio.h>
#include <string.h>

#define MAX_COUNT 	200
#define BUF_SIZE 	100


void childProcess(void)
{
	char buf[BUF_SIZE];
	for (int i = 1; i <= MAX_COUNT; i++)
	{
		// printf("Child process, value = %d\n", i);
		sprintf(buf, "child process, value = %d\n", i);		// writes to buffer
		write(1, buf, strlen(buf));							// write(<fd 1 is stdin>, *buffer, size_t writeSize)
	}
	printf("***Child process done.***");
}

void parentProcess(void)
{
	
	for (int i=1; i <= MAX_COUNT; i++)
	{
		printf("Parent process, value = %d\n", i);
	}
	printf("*** Parent process done ***\n");
}

int main(void) 
{
	pid_t pid;
	int i;
	char buf[BUF_SIZE];

	/* Example 1 */
	fork();
	pid = getpid();		// returns the childs PID
	for (i = 1; i <= MAX_COUNT; i++)
	{
		sprintf(buf, "pid %d, value = %d\n", pid, i);		// writes to buffer
		write(1, buf, strlen(buf));							// write(<fd 1 is stdin>, *buffer, size_t writeSize)
	}

	/* Example 2 */
	pid_t pid2;
	pid2 = fork();

	// bc an identical memory space is created to child process, we need to differentiate which process to call
	// fork will return pid# to parent and 0 to child.
	// based on which process is running this code.
	// on creation 
	if (pid2== 0)
		childProcess();
	else
		parentProcess();

	return 0;
}