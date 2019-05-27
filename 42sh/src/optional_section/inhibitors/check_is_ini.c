/*
** EPITECH PROJECT, 2019
** check_is_ini.c
** File description:
** check_is_ini.
*/

#include "mysh.h"

#include <stdlib.h>

int check_is_ini(shell_t *shell)
{
    int count = 0;

    for (int i = 0; shell->base_line[i] != '\0'; i++) {
        if (shell->base_line[i] == '\'' || shell->base_line[i] == '\"'
        || shell->base_line[i] == '\\')
        count++;
    }
    if (count > 0)
        return (1);
    return (0);
}
