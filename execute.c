#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "main.h"

/**
* execute - Execute a command in a child process
* @args: Array of command arguments (null-terminated)
*
* Description: Creates child process with fork() and runs command.
* Parent waits for child completion. Child runs command with execve.
* Handles basic error cases and returns appropriate status codes.
*
* Return: Child exit status if ok, -1 on error, 127 if command not found
*/
int execute(char **args)
{
	pid_t pid;
	int status;

	/* Check if arguments are valid */
	if (!args || !args[0])
	{
	fprintf(stderr, "Error: No arguments provided\n");
	return (-1);
	}
	/* Create child process */
	pid = fork();
	if (pid < 0)
	{
	perror("Error fork");
	return (-1);
	}
	/* Child process execution */
	if (pid == 0)
	{
	if (execve(args[0], args, environ) == -1)
	{
		fprintf(stderr, "Error: Command not found: %s\n", args[0]);
		exit(127);
	}
	}
	/* Parent process waits for child */
	else
	{
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("Error waitpid");
		return (-1);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	}
	return (0);
}
