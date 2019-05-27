/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** spe_realloc
*/

#include <string.h>
#include <stdlib.h>
#include <stddef.h>

char **spe_realloc(char **tab, int size)
{
    char **new_tab = malloc(sizeof(char *) * size);

    if (new_tab == NULL)
        exit(84);
    for (int i = 0; i < size - 1; i++) {
        new_tab[i] = strdup(tab[i]);
    }
    new_tab[size - 1] = NULL;
    return (new_tab);
}
