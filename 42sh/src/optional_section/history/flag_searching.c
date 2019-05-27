/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** flag_sreaching
*/

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "mysh.h"

void refet_to_dash_n(char ***history, char **args, shell_t *shell)
{
    int i;
    int nb = my_natoi(args[0], 2);

    for (i = 0; (*history)[i] != NULL; i++);
    i--;
    if (my_natoi(args[0], 2) <= 0 || i - (nb * 2 + 1) <= 0 ||
        ((*history)[i - (nb * 2)] != NULL &&
        (*history)[i - (nb * 2) + 1] != NULL &&
        (*history)[i - (nb * 2) + 2] != NULL &&
        strcmp((*history)[i - (nb * 2)], (*history)[i - (nb * 2) + 2]) == 0)) {
        my_printf("%d", (i - my_natoi(args[0], 2) * 2 + 1) / 2);
        my_putstr_err(": Event not found.\n");
        shell->return_value = 1;
        *history = spe_realloc(*history, i);
        return;
    }
    free((*history)[i]);
    (*history)[i] = strdup((*history)[i - (nb * 2)]);
    last_hist(args, *history, shell, my_natoi(args[0], 2) * 2 + 1);
}

void refer_to_n(char ***history, char **args, shell_t *shell)
{
    int i;
    int nb = my_natoi(args[0], 1);
    int save_i;

    for (i = 0; (*history)[i] != NULL; i++);
    save_i = i;
    i -= nb * 2 - 1;
    if (i <= 1 || i >= (save_i + 1) || ((*history)[nb * 2 - 1] != NULL &&
        (*history)[nb * 2] != NULL &&
        (*history)[nb * 2 + 1] != NULL &&
        strcmp((*history)[nb * 2 - 1], (*history)[nb * 2 + 1]) == 0)) {
        my_printf("%d", nb);
        my_putstr_err(": Event not found.\n");
        shell->return_value = 1;
        *history = spe_realloc(*history, save_i - 1);
        return;
    }
    free((*history)[save_i - 1]);
    (*history)[save_i - 1] = strdup((*history)[nb * 2 - 1]);
    last_hist(args, *history, shell, i);
}

int fill_string(char **args, char **history, char *str, int *i)
{
    for (int j = 1, k = 0; j < strlen(args[0]); j++, k++)
        str[k] = args[0][j];
    str[strlen(args[0]) - 1] = '\0';
    for (; history[*i] != NULL; (*i)++);
    return (*i);
}

void refer_to_str(char ***history, char **args, shell_t *shell)
{
    int i = 0;
    int j = 3;
    int save_i = 0;
    char *str = malloc(strlen(args[0]));

    if (str == NULL)
        exit(84);
    save_i = fill_string(args, *history, str, &i);
    for (int k = i - 3; k > 0; k -= 2, j += 2) {
        if (strncmp(str, (*history)[k], strlen(str)) == 0) {
            free((*history)[save_i - 1]);
            (*history)[save_i - 1] = strdup((*history)[save_i - j]);
            last_hist(args, *history, shell, j);
            return;
        }
    }
    my_putstr_err(str);
    my_putstr_err(": Event not found.\n");
    shell->return_value = 1;
    *history = spe_realloc(*history, save_i - 1);
}

void complex_flag(char ***history, char **args, shell_t *shell)
{
    int not_nb = 0;

    for (int i = 1; args[0][i] != '\0'; i++) {
        if (args[0][i] < '0' || args[0][i] > '9')
            not_nb++;
        i == 1 && args[0][i] == '-' ? not_nb-- : 0;
    }
    if (not_nb == 0 && args[0][1] != '-')
        refer_to_n(history, args, shell);
    else if (not_nb == 0)
        refet_to_dash_n(history, args, shell);
    else
        refer_to_str(history, args, shell);
}
