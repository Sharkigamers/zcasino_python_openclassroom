/*
** EPITECH PROJECT, 2019
** minishell1
** File description:
** some functions obviously
*/

#include "mysh.h"

#include <stdlib.h>
#include <stddef.h>

void print_env(shell_t *shell)
{
    for (int i = 0; shell->env_dup[i] != NULL; i++) {
        my_putstr(shell->env_dup[i]);
        my_putchar('\n');
    }
}

int my_setenv(shell_t *shell, char **args)
{
    if (args[1] == NULL)
        print_env(shell);
    else {
        int index = get_indexes(shell->env_dup);
        char *name = args[1];
        char *value = calloc(1, 1);
        if (args[2] == NULL);
        else
            value = args[2];
        if (!check_strings(args))
            return (setenv_err());
        char **dup_env = malloc(sizeof(char *) * index * 2);
        shell->env_dup = fill_env(dup_env, name, value, shell);
        update_path(name, value, shell);
        return (0);
    }
    return (0);
}

int my_unsetenv(shell_t *shell, char **args)
{
    int rem_ind = 0;

    if (args[1] == NULL) {
        my_putstr_err("unsetenv: Too few arguments.\n");
        return (0);
    }
    for (; args[rem_ind] != NULL; rem_ind++);
    for (int i = 1; rem_ind != 1; rem_ind--, i++) {
        shell->env_dup = remove_index(args[i], shell);
        update_path(args[i], NULL, shell);
    }
    return (0);
}

int functions(char *string, shell_t *shell, char **args, tree_t **right)
{
    if (my_strcmp(string, "exit") == 0)
        my_exit(args, shell);
    if (my_strcmp(string, "cd") == 0) {
        my_cd(shell, args);
        return (1);
    } if (my_strcmp(string, "setenv") == 0) {
        my_setenv(shell, args);
        return (1);
    } if (my_strcmp(string, "env") == 0) {
        print_env(shell);
        return (1);
    } if (my_strcmp(string, "unsetenv") == 0) {
        my_unsetenv(shell, args);
        return (1);
    } if (my_strcmp(string, "alias") == 0) {
        my_alias(shell, args);
        return (1);
    }
    return (check_other_functions(string, shell, args));
}
