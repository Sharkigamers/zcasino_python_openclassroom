/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** abc
*/

#include "mysh.h"

#include <stddef.h>
#include <stdlib.h>

int is_present(char **tab)
{
    int i = 0;
    char *name = NULL;

    for (; tab[i] != NULL; i++) {
        name = get_name(tab[i]);
        if (!my_strcmp(name, "OLDPWD")) {
            free(name);
            return (1);
        }
        free(name);
    }
    return (0);
}

static char **get_new_tab(char **tab)
{
    int index = get_indexes(tab);
    int count = 0;
    char **new_tab = malloc(sizeof(char *) * (index * 2));
    char *name = NULL;

    for (int i = 0; i != index; i++, count++) {
        name = get_name(tab[i]);
        if (!my_strcmp(name, "OLDPWD"))
            count--;
        else
            new_tab[count] = tab[i];
        free(name);
    }
    new_tab[count] = NULL;
    new_tab[count + 1] = NULL;
    return (new_tab);
}

void remove_oldpwd(shell_t *shell)
{
    char *args[] = {"unsetenv", "OLDPWD", NULL};

    if (is_present(shell->env_dup))
        shell->env_dup = get_new_tab(shell->env_dup);
}
