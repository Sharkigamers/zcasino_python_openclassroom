/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** mount_flag
*/

#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#include "mysh.h"

static void fill_tab(char **tab, char **new_tab)
{
    int k = 0;

    for (int j = 0; tab[j] != NULL && tab[j + 1] != NULL;
        j += 2) {
        if (strcmp(tab[j + 1], "history\n") != 0) {
            new_tab[k] = strdup(tab[j]);
            new_tab[k + 1] = strdup(tab[j + 1]);
            k += 2;
        }
    }
    new_tab[k] = NULL;
}

static char **my_sperealloc(char **tab)
{
    char **new_tab;
    int sub = 0;
    int i = 0;

    for (i = 0; tab[i] != NULL && tab[i + 1] != NULL; i += 2) {
        if (strcmp(tab[i + 1], "history\n") == 0)
            sub += 2;
    }
    new_tab = malloc(sizeof(char *) * (i - sub + 1));
    if (new_tab == NULL)
        return (NULL);
    fill_tab(tab, new_tab);
    for (int i = 0; tab[i] != NULL; i++)
        free(tab[i]);
    free(tab);
    return (new_tab);
}

void history_flag_maj_m(char ***history, shell_t *shell)
{
    int i;

    for (i = 0; (*history)[i] != NULL; i++);
    shell->history_adder += i / 2;
    shell->history_pointer = 0;
    *history = my_sperealloc(*history);
}
