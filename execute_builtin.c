#include "main.h"

#define PROMPT "$ "

/**
 * execute_builtin - Checks and executes built-in commands
 * @args: Command arguments
 * Return: -1 for exit, 0 for success, 1 if not builtin
 */
int execute_builtin(char **args)
{
    builtin_t builtins[] = {
        {"exit", builtin_exit},
        {"env", builtin_env},
        {NULL, NULL}
    };
    int i;

    if (!args || !args[0])
        return (1);

    for (i = 0; builtins[i].name; i++)
    {
        if (strcmp(args[0], builtins[i].name) == 0)
            return (builtins[i].func(args));
    }
    return (1);
}
