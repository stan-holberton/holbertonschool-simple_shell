#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"

char **split_line(char *line)
{
    char **args = NULL;
    char *token;
    size_t bufsize = 64, i = 0;

    args = malloc(bufsize * sizeof(char *));
    if (!args)
    {
        perror("Erreur d'allocation mémoire");
        return (NULL);
    }

    token = strtok(line, " ");
    while (token)
    {
        args[i++] = token;

        if (i >= bufsize)
        {
            bufsize += 64;
            args = realloc(args, bufsize * sizeof(char *));
            if (!args)
            {
                perror("Erreur de réallocation mémoire");
                return (NULL);
            }
        }

        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    return (args);
}
