#include <stdlib.h>
#include <stdio.h>
#include "main.h"

/**
 * builtin_exit - Handles the exit command to terminate the shell.
 * @args: Array of arguments (not used here).
 * Return: -1 if the shell should terminate, 0 otherwise.
 */
int builtin_exit(char **args)
{
	(void)args; /* Arguments are not used for "exit". */
	return (-1); /* Returns a special value indicating the shell should stop. */
}
