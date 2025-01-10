#include "main.h"

/**
 * execute - Execute a command in a child process
 * @args: Array of command arguments (null-terminated)
 * Return: Child exit status if ok, -1 on error
 */
int execute(char **args)
{
    pid_t pid;
    int status;

    if (!args || !args[0])
        return (-1);

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return (-1);
    }

    if (pid == 0)
    {
        if (execve(args[0], args, environ) == -1)
        {
            perror(args[0]);
            exit(127);
        }
    }
    else
    {
        if (waitpid(pid, &status, 0) == -1)
        {
            perror("waitpid");
            return (-1);
        }
        if (WIFEXITED(status))
            return (WEXITSTATUS(status));
    }
    return (0);
}
