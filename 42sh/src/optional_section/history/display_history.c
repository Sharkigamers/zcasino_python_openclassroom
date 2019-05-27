/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** display_history
*/

#include <time.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#include "mysh.h"

int for_number(char **history, shell_t *shell)
{
    int i = 0;
    int k = 0;

    for (; history[i] != NULL; i++);
    for (i = i - 1; k < shell->hist_flag[12] && i > 0; i -= 2) {
        if (i >= 3 && strcmp(history[i], history[i - 2]) == 0)
            continue;
        k++;
    }
    i < 0 ? i = 0 : -1;
    i < shell->history_pointer ? i = shell->history_pointer - 1 : 0;
    return (i + 1);
}

void get_and_print_time(char *str_time)
{
    size_t real_time = my_ngetnbr(str_time, 2);
    char *get_time = ctime(&real_time);
    int i = 0;

    for (int space = 0; space < 3 && get_time[i] != '\0'; i++)
        get_time[i] == ' ' ? space++ : 0;
    for (int tp = 0; tp < 2 && get_time[i] != '\0'; i++) {
        get_time[i] == ':' ? tp++ : 0;
        if (tp >= 2)
            break;
        my_printf("%c", get_time[i]);
    }
}

void disp_start_spaces(int i)
{
    char *convert_i = my_itoa(i);
    int nb_space = 6 - strlen(convert_i);

    for (int i = 0; i < nb_space; i++)
        my_printf(" ");
    free(convert_i);
}

void display_history(char **history, shell_t *shell)
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
        disp_start_spaces(i / 2 + shell->history_adder + 1);
        my_printf("%d\t", i / 2 + shell->history_adder + 1);
        get_and_print_time(history[i]);
        if (history[i + 1] != NULL)
            my_printf("\t%s", history[i + 1]);
    }
    shell->return_value = 0;
}
