#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "main.h"

#define PROMPT "$ "

/**
 * main - Main function of a simple command-line interpreter (shell)
 *
 * This function implements a basic shell that:
 * - Displays a prompt in interactive mode
 * - Reads user input
 * - Processes the commands
 * - Executes them
 * - Repeats until exit
 *
 * Return: 0 on successful execution
 */
int main(void)
{
	char *userInput = NULL;/* Stores the user's input string */
	size_t inputBufferSize = 0;/* Size of the input buffer */
	ssize_t bytesRead;/* Number of bytes read from input */
	char **commandArguments;/* Array of command arguments */
	size_t argIndex;/* Index for freeing command arguments */
	int interactive;/* Flag for interactive mode */

	/* Check if the shell is in interactive mode */
	interactive = isatty(STDIN_FILENO);

	while (1)
	{
		/* Display prompt only in interactive mode */
		if (interactive)
			write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
		bytesRead = getline(&userInput, &inputBufferSize, stdin);
		/* Handle EOF (Ctrl+D) or error in input */
		if (bytesRead == -1)
		{
			free(userInput);
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}
		/* Remove trailing newline character */
		userInput[strcspn(userInput, "\n")] = '\0';
		if (strlen(userInput) == 0)
			continue;
		/* Split the input line into command and arguments */
		commandArguments = split_line(userInput);
		if (!commandArguments)
			continue;
		execute(commandArguments);
		/* Clean up allocated memory for command arguments */
		for (argIndex = 0; commandArguments[argIndex] != NULL; argIndex++)
			free(commandArguments[argIndex]);
		free(commandArguments);
	}
return (0);
}
