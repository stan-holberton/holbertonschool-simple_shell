#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "main.h"

/* Déclaration explicite de environ */
extern char **environ;

/**
 * execute - Crée un processus enfant, exécute une commande et attend la fin.
 * @args: Tableau d'arguments de la commande (args[0] doit contenir le chemin complet).
 *
 * Return: Code de retour du processus enfant ou -1 en cas d'erreur.
 */
int execute(char **args)
{
    pid_t pid;
    int status;

    /* Création du processus enfant */
    pid = fork();

    if (pid < 0) /* Gestion d'erreur pour fork() */
    {
        perror("Erreur lors de la création du processus");
        return (-1);
    }

    if (pid == 0) /* Processus enfant */
    {
        if (execve(args[0], args, environ) == -1) /* Exécute la commande */
        {
            perror("Erreur lors de l'exécution de la commande");
            exit(EXIT_FAILURE); /* Quitte le processus enfant si execve échoue */
        }
    }
    else /* Processus parent */
    {
        /* Attente de la fin du processus enfant */
        wait(&status);

        /* Retourne le code de sortie du processus enfant */
        if (WIFEXITED(status))
            return (WEXITSTATUS(status));
    }

    return (0);
}
