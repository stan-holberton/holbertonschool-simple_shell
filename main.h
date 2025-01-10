#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

/* External environment variable */
extern char **environ;

/**
 * struct builtin_s - Structure for built-in commands
 * @name: Name of the built-in command
 * @func: Function pointer to the built-in implementation
 */
typedef struct builtin_s
{
	char *name;
	int (*func)(char **);
} builtin_t;

/* Function prototypes */
int execute(char **args);
char **split_line(char *line);
char *find_in_path(char *cmd);
char *check_access(char *cmd);
int builtin_exit(char **args);
int builtin_env(char **args);
int execute_builtin(char **args);

#endif /* MAIN_H */
