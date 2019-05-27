/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** history_flag
*/

#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>

#include "mysh.h"

void another_filling_history(shell_t *shell, char history_char)
{
    switch (history_char) {
    case 'M':
        shell->hist_flag[10] = 1;
        break;
    case 'T':
        shell->hist_flag[11] = 1;
        break;
    }
}

void more_filling_history(shell_t *shell, char history_char)
{
    switch (history_char) {
    case 'p':
        shell->hist_flag[5] = 1;
        break;
    case 's':
        shell->hist_flag[6] = 1;
        break;
    case 'h':
        shell->hist_flag[7] = 1;
        break;
    case 'S':
        shell->hist_flag[8] = 1;
        break;
    case 'L':
        shell->hist_flag[9] = 1;
        break;
    default:
        another_filling_history(shell, history_char);
    }
}

void fill_history_flag(shell_t *shell, char history_char)
{
    switch (history_char) {
    case 'a':
        shell->hist_flag[0] = 1;
        break;
    case 'n':
        shell->hist_flag[1] = 1;
        break;
    case 'r':
        shell->hist_flag[2] = 1;
        break;
    case 'w':
        shell->hist_flag[3] = 1;
        break;
    case 'c':
        shell->hist_flag[4] = 1;
        break;
    default:
        more_filling_history(shell, history_char);
    }
}

void check_history_flags(shell_t *shell, char **args)
{
    for (int i = 1; args[i] != NULL; i++) {
        for (int j = 0; args[i][j] != '\0'; j++) {
            fill_history_flag(shell, args[i][j]);
        }
        if (args[i][0] >= '0' && args[i][0] <= '9' && shell->hist_flag[12] == 0)
            shell->hist_flag[12] = atoi(args[i]);
    }
}
