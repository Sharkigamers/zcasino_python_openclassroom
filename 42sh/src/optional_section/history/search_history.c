/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** search_history
*/

#include "mysh.h"

int search_in_history(char ***history, shell_t *shell, char **args)
{
    if (my_strcmp(args[0], "!") == 0) {
        my_putstr_err("!: Command not found.\n");
        shell->return_value = 1;
        return (1);
    }
    if (my_strcmp(args[0], "!!") == 0) {
        shell->detect_free = 1;
        last_hist(args, *history, shell, 3);
        return (0);
    }
    if (args[0][0] == '!') {
        shell->detect_free = 0;
        complex_flag(history, args, shell);
        return (0);
    }
}
