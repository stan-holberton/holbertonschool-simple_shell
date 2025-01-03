#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"

/**
 * split_line - Divise une chaîne en un tableau de mots (tokens).
 * @line: La chaîne à diviser.
 *
 * Retourne: Un tableau de pointeurs vers les mots, terminé par NULL.
 */
char **split_line(char *line)
{
    char **words = NULL; /* Tableau pour stocker les mots */
    char *current_word;  /* Contient temporairement chaque mot extrait */
    char **reallocated_words; /* Utilisé pour la réallocation */
    size_t buffer_size = 64, word_count = 0; /* Taille initiale et compteur de mots */

    /* Allocation initiale du tableau */
    words = malloc(buffer_size * sizeof(char *));
    if (!words) /* Vérification de l'allocation mémoire */
    {
        perror("Erreur d'allocation mémoire");
        return (NULL);
    }

    /* Division de la ligne en mots, en utilisant l'espace comme délimiteur */
    current_word = strtok(line, " ");
    while (current_word)
    {
        /* Duplication du mot extrait pour le stocker indépendamment */
        words[word_count] = strdup(current_word);
        if (!words[word_count]) /* Vérification de l'allocation mémoire pour chaque mot */
        {
            perror("Erreur d'allocation mémoire");
            /* Libération de la mémoire déjà allouée en cas d'erreur */
            while (word_count > 0)
                free(words[--word_count]);
            free(words);
            return (NULL);
        }

        word_count++; /* Incrément du compteur de mots */

        /* Vérification si le tableau doit être agrandi */
        if (word_count >= buffer_size)
        {
            buffer_size += 64; /* Augmentation de la taille */
            reallocated_words = realloc(words, buffer_size * sizeof(char *)); /* Réallocation */
            if (!reallocated_words) /* Vérification de la réallocation */
            {
                perror("Erreur de réallocation mémoire");
                /* Libération de toute la mémoire allouée en cas d'échec */
                while (word_count > 0)
                    free(words[--word_count]);
                free(words);
                return (NULL);
            }
            words = reallocated_words; /* Mise à jour du tableau */
        }

        current_word = strtok(NULL, " "); /* Extraction du mot suivant */
    }

    words[word_count] = NULL; /* Marque la fin du tableau */
    return (words); /* Retour du tableau de mots */
}
