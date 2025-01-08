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
	char *userInput = NULL;
	size_t inputBufferSize = 0;
	ssize_t bytesRead;
	char **commandArguments;
	size_t argIndex;
	int interactive;

	interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (interactive)
			write(STDOUT_FILENO, PROMPT, strlen(PROMPT));

		bytesRead = getline(&userInput, &inputBufferSize, stdin);
		if (bytesRead == -1)
		{
			free(userInput);
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}
		userInput[strcspn(userInput, "\n")] = '\0';
		if (strlen(userInput) == 0)
			continue;
		commandArguments = split_line(userInput);
		if (!commandArguments)
			continue;
		execute(commandArguments);
		for (argIndex = 0; commandArguments[argIndex] != NULL; argIndex++)
			free(commandArguments[argIndex]);
		free(commandArguments);
	}
	return (0);
}
