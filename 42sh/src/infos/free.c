/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** il a tout compris
*/

#include "mysh.h"
#include <stddef.h>
#include <stdlib.h>

void free_tab(char **tab)
{
    if (tab == NULL)
        return;
    for (int i = 0; i != get_indexes(tab); i++)
        free(tab[i]);
    free(tab);
}

void free_utility(char *bin , char **args)
{
    free_tab(args);
    free(bin);
}

void free_shell(shell_t *shell)
{
    free_tab(shell->path);
    free(shell->home);
    free(shell->base_line);
    free(shell);
}
