/*
** EPITECH PROJECT, 2019
** is_repeat.c
** File description:
** is_repeat.
*/

#include "mysh.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void is_repeat(shell_t *shell, char **args)
{
    int count = 0;

    for (; args[count] != NULL; count++);
    count--;
    if (count == 0 || count == 1) {
        dprintf(1, "repeat: Too few arguments.\n");
        shell->return_value = 1;
        return;
    }
    for (int j = 0; args[2][j] != '\0'; j++) {
        if (args[2][j] > '0' || args[2][j] < '9') {
            dprintf(1, "repeat: Badly formed number.\n");
            shell->return_value = 1;
            return;
        }
    }
    return;
}
