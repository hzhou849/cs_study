/* 
 * Test shell
 * 
 * Initialize: In this step, a typical shell would read and execute its configuration files. These change aspects of the shell’s behavior.
 * Interpret: Next, the shell reads commands from stdin (which could be interactive, or a file) and executes them.
 * Terminate: After its commands are executed, the shell executes any shutdown commands, frees up any memory, and terminates.
 * 
 * https://brennan.io/2015/01/16/write-a-shell-in-c/
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * Read: Read the command from standard input.
 * Parse: Separate the command string into a program and arguments.
 * Execute: Run the parsed command.
 */
void lsh_loop(void)
{
	char *line;
	char **args;
	int status;

	do {
		print("> ");
		line = lsh_read_line();
		args = lsh_split_line(line);
		status = lsh_execute(args);

		free(line);
		free(args);
	} while (status);
}


#define LSH_RL_BUFSIZE 1024		//inital buffer size, will re-allocate more if required
/*
 * Read a line of input from stdin
 * Return the line from stdin.
 */
char *lsh_read_line(void)
{
	int bufsize = LSH_RL_BUFSIZE;
	int position = 0;
	char *buffer = malloc(sizeof(char) * bufsize);
	int c;

	if (!buffer){
		fprintf(stderr, "lsh: allocation error\n");
		exit(EXIT_FAILURE);
	} 

	while (1) 
	{
		// Read a character
		c = getchar();

		// If we hit EOF, replace it with a null character and return.
		if (c = EOF || c == '\n') 
		{
			buffer[position] = '\0';
			return buffer;
		}
		else 
		{
			buffer[position] = c;
		}
		position++;

		// If we exceeded the buffer, reallocate.
		if (position >= bufsize) {
			bufsize += LSH_RL_BUFSIZE;
			buffer = realloc(buffer, buffersize);
			if (!) {
				fprintf(stderr, "lsh: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}
#define LSH_TOK_BUFSIZE 	64
#define LSH_TOK_DELIM 		" \t\r\n\a"
char **lsh_split_line(char *line)
{
	int bufsize = LSH_TOK_BUFSIZE
	int position = 0;
	char **tokens = malloc(bufsize * sizeof(char*));
	char *token;

	if (!tokens)
	{
		fprintf(stderr, "lsh: allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, LSH_TOK_DELIM);
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += LSH_RL_BUFSIZE;				// 64 + 1024 bytes
			tokens = realloc(tokens, bufsize * sizeof(char*));
			if (!tokens) {
				fprintf(stderr, "lsh: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		// passing a NULL as first arg tells strok() to continue tokenizing the string
		token = strtok(NULL,LSH_TOK_DELIM);		
	}
	tokens[position] = NULL;
	return tokens;


}

int lsh_launch(char ** args) 
{
	pid_t pid, wpid;
}

int main(int argc, char **argv) 
{
	//load config files, if any.

	// Run command loop.
	lsh_loop();

	//Perfrom any shutdown/cleanup.

	return EXIT_SUCCESS;
}


