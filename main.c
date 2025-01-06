#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "main.h"

#define PROMPT "$ " /* Définition de l'invite de commande */
/**
 * main - Fonction principale d'un interpréteur de commandes simple.
 *
 * Return: 0 en cas de succès.
 */
int main(void)
{
	char *userInput = NULL; /* Chaîne pour stocker l'entrée utilisateur */
	size_t inputBufferSize = 0; /* Taille du tampon pour getline */
	ssize_t bytesRead; /* Nombre de caractères lus par getline */
	char **commandArguments; /* Tableau pour stocker les arguments */
	size_t argIndex; /* Index pour parcourir et libérer les arguments */
		while (1) /* Boucle infinie pour traiter les commandes en continu */
	{
		/* Affichage de l'invite de commande */
		write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
		/* Lecture de l'entrée utilisateur */
		bytesRead = getline(&userInput, &inputBufferSize, stdin);
		if (bytesRead == -1) /* Vérification de fin de fichier ou d'erreur */
		{
			free(userInput); /* Libération de la mémoire de l'entrée utilisateur */
			write(STDOUT_FILENO, "\n", 1); /* Ajout d'une nouvelle ligne */
			break;
		}
		/* Suppression du caractère de nouvelle ligne à la fin de l'entrée */
		userInput[strcspn(userInput, "\n")] = '\0';
		/* Si l'entrée est vide, on retourne au début de la boucle */
		if (strlen(userInput) == 0)
			continue;
		/* Découpe l'entrée en arguments de commande */
		commandArguments = split_line(userInput);
		if (!commandArguments) /* Vérification de l'échec de la découpe */
			continue;
		/* Exécute la commande spécifiée par l'utilisateur */
		execute(commandArguments);
		/* Libération de la mémoire des arguments */
		for (argIndex = 0; commandArguments[argIndex] != NULL; argIndex++)
			free(commandArguments[argIndex]); /* Libère chaque argument */
		free(commandArguments); /* Libère le tableau des arguments */
	}
	return (0); /* Indique que le programme s'est terminé avec succès */
}

