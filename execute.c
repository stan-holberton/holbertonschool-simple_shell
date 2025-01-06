#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "main.h"
/**
 * execute - Exécute une commande dans un processus enfant.
 * @args: Tableau d'argutments de la commande.
 *
 * Return: Code de retour du processus enfant ou -1 en cas d'erreur.
 */
int execute(char **args)
{
	pid_t pid;
	int status;

	if (!args || !args[0])
	{
		fprintf(stderr, "Erreur : Aucun argument fourni\n");
		return (-1);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("Erreur fork");
		return (-1);
	}
		if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			fprintf(stderr, "Erreur : Commande introuvable : %s\n", args[0]);
			exit(127);
		}
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("Erreur waitpid");
			return (-1);
		}
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (0);
}
