/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** contain other built ins
*/

#include <string.h>
#include <stdlib.h>
#include <stddef.h>

#include "mysh.h"

int check_optional_function(char *string, shell_t *shell, char **args)
{
    if (my_strcmp(string, "where") == 0) {
        my_where(shell, args);
        return (1);
    } if (my_strcmp(string, "which") == 0) {
        my_which(shell, args);
        return (1);
    } if (error_backchar(shell) == 1)
        return (1);
    return (0);
}

int check_other_functions(char *string, shell_t *shell, char **args)
{
    if (string[0] == '!') {
        if (search_in_history(&shell->history, shell, args) == 1)
            return (1);
        return (1);
    } if (strcmp(string, "history") == 0) {
        if (check_flags(args, shell) == 1)
            return (1);
        check_history_flags(shell, args);
        which_flag(shell, &shell->history, args);
        reinit_hist_var(shell);
        return (1);
    } if (my_strcmp(string, "echo") == 0) {
        my_echo(shell, args);
        return (1);
    } if (check_optional_function(string, shell, args) == 1)
        return (1);
    return (0);
}

char *get_name(char *env_str)
{
    char *res = calloc(1, sizeof(char) * my_strlen(env_str));
    int i = 0;

    if (res == NULL)
        exit(84);
    for (; env_str[i] != '\0'; i++) {
        if (env_str[i] == '=') {
            res[i] = '\0';
            break;
        }
        res[i] = env_str[i];
    }
    return (res);
}
