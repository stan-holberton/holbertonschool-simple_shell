#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "main.h"

/**
 * check_access - Checks if a command is executable as is.
 * @cmd: The command to check.
 *
 * Return: A duplicated string if the command is executable, NULL otherwise.
 */
char *check_access(char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (strdup(cmd));
	return (NULL);
}

/**
 * find_in_path - Finds the full path of a command in the PATH.
 * @cmd: Command to locate (e.g., "ls").
 *
 * Return: Dynamically allocated string (must be freed) or NULL if not found.
 */
char *find_in_path(char *cmd)
{
	char *path_env, *path_copy, *dir, *full_path;
	size_t full_path_len;

	full_path = check_access(cmd);
	if (full_path)
		return (full_path);

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);

	path_copy = strdup(path_env);
	if (!path_copy)
	{
		perror("Memory allocation error");
		return (NULL);
	}

	dir = strtok(path_copy, ":");
	while (dir)
	{
		full_path_len = strlen(dir) + strlen(cmd) + 2;
		full_path = malloc(full_path_len);
		if (!full_path)
		{
			perror("Memory allocation error");
			free(path_copy);
			return (NULL);
		}
		snprintf(full_path, full_path_len, "%s/%s", dir, cmd);
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
