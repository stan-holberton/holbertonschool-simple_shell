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

    /* Vérification des arguments */
    if (!args || !args[0])
    {
        fprintf(stderr, "Erreur : Aucun argument fourni à execute\n");
        return (-1);
    }

    /* Création du processus enfant */
    pid = fork();
    if (pid < 0) /* Gestion d'erreur pour fork() */
    {
        perror("Erreur lors de la création du processus");
        return (-1);
    }

    if (pid == 0) /* Processus enfant */
    {
        /* Exécution de la commande */
        if (execve(args[0], args, environ) == -1)
        {
            perror("Erreur lors de l'exécution de la commande");
            exit(127); /* Code de retour standard pour commande non trouvée */
        }
    }
    else /* Processus parent */
    {
        /* Attente de la fin du processus enfant */
        if (wait(&status) == -1)
        {
            perror("Erreur lors de l'attente du processus enfant");
            return (-1);
        }

        /* Retourne le code de sortie du processus enfant */
        if (WIFEXITED(status))
            return (WEXITSTATUS(status));
    }

    return (0);
}
