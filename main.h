#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

extern char **environ;

int execute(char **args);
char **split_line(char *line);
char *check_access(char *cmd);
int builtin_exit(char **args);
char *find_in_path(char *cmd);

#endif
