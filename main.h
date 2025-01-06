#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

/* Déclaration explicite de environ */
extern char **environ;

/* Prototypes */
int execute(char **args);
char **split_line(char *line);

#endif /* MAIN_H */
