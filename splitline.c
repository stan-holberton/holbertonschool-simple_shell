#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#define BUFFER_SIZE 64
/**
 * split_line - Divise une chaîne en un tableau de mots.
 * @line: La chaîne à diviser.
 *
 * Return: Un tableau de pointeurs vers les mots, terminé par NULL.
 */
char **split_line(char *line)
{
	char **words = NULL, *word;
	size_t count = 0, size = BUFFER_SIZE;
words = malloc(size * sizeof(char *));

	if (!words)
		return (NULL);
	word = strtok(line, " ");
	while (word)
	{
		words[count] = strdup(word);
		if (!words[count])
		{
			while (count > 0)
				free(words[--count]);
			free(words);
			return (NULL);
}
		count++;
		if (count >= size)
		{
			size += BUFFER_SIZE;
			words = realloc(words, size * sizeof(char *));
			if (!words)
				return (NULL);
	}
		word = strtok(NULL, " ");
	}
	words[count] = NULL;
	return (words);
}
