#include "main.h"

#define BUFFER_SIZE 64

/**
 * split_line - Splits a string into an array of words
 * @line: The string to split
 * Return: Array of strings, NULL on failure
 */
char **split_line(char *line)
{
    char **tokens = NULL;
    char *token;
    size_t count = 0, size = BUFFER_SIZE;

    if (!line)
        return (NULL);

    tokens = malloc(size * sizeof(char *));
    if (!tokens)
        return (NULL);

    token = strtok(line, " \t\r\n\a");
    while (token)
    {
        tokens[count] = strdup(token);
        if (!tokens[count])
        {
            while (count > 0)
                free(tokens[--count]);
            free(tokens);
            return (NULL);
        }
        count++;
        if (count >= size)
        {
            size += BUFFER_SIZE;
            tokens = realloc(tokens, size * sizeof(char *));
            if (!tokens)
                return (NULL);
        }
        token = strtok(NULL, " \t\r\n\a");
    }
    tokens[count] = NULL;
    return (tokens);
}
