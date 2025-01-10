#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define PROMPT "$ "

/**
 * main - Main function of the shell
 * Return: 0 on successful execution
 */
int main(void)
{
	char *input = NULL;
	size_t bufsize = 0;
	ssize_t chars_read;
	char **args;
	int status = 0, builtin_status;
	size_t i;
	int interactive = isatty(STDIN_FILENO);
	char *cmd_path;

	while (1)
	{
		if (interactive)
			write(STDOUT_FILENO, PROMPT, 2);

		chars_read = getline(&input, &bufsize, stdin);
		if (chars_read == -1)
		{
			free(input);
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			exit(status);
		}

		input[strcspn(input, "\n")] = '\0';
		if (strlen(input) == 0)
			continue;

		args = split_line(input);
		if (!args)
			continue;

		builtin_status = execute_builtin(args);
		if (builtin_status != 1)
		{
			status = builtin_status;
			for (i = 0; args[i]; i++)
				free(args[i]);
			free(args);
			if (builtin_status == -1)
				break;
			continue;
		}

		cmd_path = find_in_path(args[0]);
		if (cmd_path)
		{
			free(args[0]);
			args[0] = cmd_path;
			status = execute(args);
		}
		else
		{
			write(STDERR_FILENO, args[0], strlen(args[0]));
			write(STDERR_FILENO, ": command not found\n", 20);
			status = 127;
		}

		for (i = 0; args[i]; i++)
			free(args[i]);
		free(args);
	}
	free(input);
	return (status);
}
