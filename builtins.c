#include "main.h"

/**
 * builtin_exit - Handles the exit command
 * @args: Command arguments (unused)
 * Return: -1 to exit the shell
 */
int builtin_exit(char **args)
{
    (void)args;
    return (-1);
}

/**
 * builtin_env - Prints the current environment
 * @args: Command arguments (unused)
 * Return: Always returns 0
 */
int builtin_env(char **args)
{
    int i;

    (void)args;
    for (i = 0; environ[i]; i++)
    {
        write(STDOUT_FILENO, environ[i], strlen(environ[i]));
        write(STDOUT_FILENO, "\n", 1);
    }
    return (0);
}
