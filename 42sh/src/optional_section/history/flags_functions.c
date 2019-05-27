/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** functions for history flags
*/

#include <string.h>
#include <stddef.h>

#include "mysh.h"

int history_flag_c(char **history)
{
    int i = 0;

    for (; history[i] != NULL; i++);
    return (i);
}

void cond_for_flag_r(shell_t *shell, int j, int k, char **history)
{
    if (shell->hist_flag[7] != 1) {
        disp_start_spaces(j / 2 + shell->history_adder + 1 + k);
        my_printf("%d\t", j / 2 + shell->history_adder + 1 + k);
        (j - 1 >= 0) ? get_and_print_time(history[j - 1]) : 0;
        my_printf("\t");
    }
    if (j >= 0 && history[j] != NULL)
        my_printf("%s", history[j]);
}

void history_flag_r(char **history, shell_t *shell)
{
    int i;
    int k = 0;
    int l = 0;

    if (shell->hist_flag[12] != 0)
        l = for_number(history, shell);
    for (i = 0; history[i + 1] != NULL; i++);
    for (int j = i; j > l; j -= 2) {
        if (j >= 3 && j >= l + 3 && history[j - 2] != NULL &&
            history[j - 3] != NULL && strcmp(history[j], history[j - 2]) == 0) {
            k++;
            continue;
        }
        if (shell->history_pointer != 0 && j <= shell->history_pointer)
            break;
        cond_for_flag_r(shell, j, k, history);
        k = 0;
    }
}

void history_flag_h(char **history, shell_t *shell)
{
    int i;

    if (shell->hist_flag[12] == 0)
        i = shell->history_pointer;
    else
        i = for_number(history, shell);
    for (; history[i] != NULL && history[i + 1] != NULL; i += 2) {
        if (history[i + 2] != NULL && history[i + 3] != NULL &&
            strcmp(history[i + 1], history[i + 3]) == 0)
            continue;
        my_printf("%s", history[i + 1]);
    }
}
