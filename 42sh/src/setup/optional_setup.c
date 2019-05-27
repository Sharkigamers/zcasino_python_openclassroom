/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** optionnal_setup
*/

#include <string.h>
#include <stddef.h>
#include <stdlib.h>

#include "mysh.h"

void reinit_hist_var(shell_t *shell)
{
    free(shell->hist_flag);
    setup_basic_hist_var(shell);
}

int setup_basic_hist_var(shell_t *shell)
{
    shell->hist_flag = malloc(sizeof(int) * (13 + 1));
    if (shell->hist_flag == NULL)
        exit(84);
    for (int i = 0; i < 13; i++)
        shell->hist_flag[i] = 0;
    shell->detect_free = 0;
    shell->history_adder = 0;
    shell->doors = 0;
    return (0);
}

char **path_replacement(void)
{
    char **new_path = malloc(sizeof(char *) * 3);

    if (new_path == NULL)
        exit(84);
    new_path[0] = "/bin/";
    new_path[1] = NULL;
    new_path[2] = NULL;
    return (new_path);
}
