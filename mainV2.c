#include "main.h"
#define PROMPT "$ "
/**
 * main - Point d'entrée du programme simple shell
 *
 * Description: Ce programme affiche un prompt, lit l'entrée de l'utilisateur,
 * découpe cette entrée en arguments, et exécute la commande correspondante.
 * La boucle continue jusqu'à ce que l'utilisateur quitte
 * (par exemple avec Ctrl+D).
 *
 * Return: Toujours 0 (Succès)
 */
int main(void)
{
	char *userInput = NULL; /*ligne d'entrée utilisateur*/
	size_t inputBufferSize = 0; /*taille du buffer d'entrée*/
	ssize_t bytesRead; /*taille du buffer d'entrée*/
	char **commandArguments; /**/

	while (1)
	{
		write(STDOUT_FILENO, PROMPT, strlen(PROMPT)); /* Afficher le prompt */
		bytesRead = getline(&userInput, &inputBufferSize, stdin);
		/* Lire l'entrée utilisateur */
		if (bytesRead == -1) /*Gestion de Ctrl+D*/
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}
		/* Supprimer le '\n' de getline */
		userInput[strcspn(userInput, "\n")] = '\0';
		/* Vérifier si une commande a été saisie */
		if (strlen(userInput) == 0)
			continue;
		/* Découper la ligne en arguments */
		commandArguments = split_line(userInput);
		if (!commandArguments)
			continue;
		/* Exécuter la commande */
		execute(commandArguments);
		/* Libérer la mémoire allouée pour commandArguments */
		free(commandArguments);
		}
	/* Libérer les ressources */
	free(userInput);
	return (0);
}
