#include "main.h"

/**
 * check_access - Checks if a command is executable
 * @cmd: The command to check
 * Return: Duplicated string if executable, NULL otherwise
 */
char *check_access(char *cmd)
{
    if (!cmd)
        return (NULL);

    if (access(cmd, X_OK) == 0)
        return (strdup(cmd));

    return (NULL);
}

/**
 * find_in_path - Finds command in PATH
 * @cmd: Command to locate
 * Return: Full path if found, NULL otherwise
 */
char *find_in_path(char *cmd)
{
    char *path_env, *path_copy, *dir, *full_path;
    size_t path_len;

    if (!cmd)
        return (NULL);

    full_path = check_access(cmd);
    if (full_path)
        return (full_path);

    path_env = getenv("PATH");
    if (!path_env)
        return (NULL);

    path_copy = strdup(path_env);
    if (!path_copy)
        return (NULL);

    dir = strtok(path_copy, ":");
    while (dir)
    {
        path_len = strlen(dir) + strlen(cmd) + 2;
        full_path = malloc(path_len);
        if (!full_path)
        {
            free(path_copy);
            return (NULL);
        }
        snprintf(full_path, path_len, "%s/%s", dir, cmd);
        if (access(full_path, X_OK) == 0)
        {
            free(path_copy);
            return (full_path);
        }
        free(full_path);
        dir = strtok(NULL, ":");
    }
    free(path_copy);
    return (NULL);
}
