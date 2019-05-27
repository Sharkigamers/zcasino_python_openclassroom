/*
** EPITECH PROJECT, 2019
** minishell1
** File description:
** exec other functions
*/

#include "mysh.h"

#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>

char *update_wave(char *line, shell_t *shell)
{
    char *new_str = calloc(1, sizeof(char) * my_strlen(line));
    int i = 0;

    if (shell->home == NULL)
        return (NULL);
    for (; i != my_strlen(line); i++)
        new_str[i] = line[i + 1];
    new_str = my_strcat(shell->home, new_str);
    return (new_str);
}

int is_a_binary(char *line, char **args, shell_t *shell, tree_t **right)
{
    int status = 0;

    if (opendir(line) != NULL)
        shell->dir_error = 1;
    if (!is_a_wave(line, args, shell))
        return (0);
    for (; args[status] != NULL; status++);
    return (is_completed(line, args, shell, right));
}

char **remove_index(char *string, shell_t *shell)
{
    int total_indexes = get_indexes(shell->env_dup);
    int new_index = 0;
    char **new_env = malloc(sizeof(char *) * total_indexes * 2);
    int i = 0;

    for (i = 0; shell->env_dup[i] != NULL; i++, new_index++) {
        if (!my_strcmp(string, get_name(shell->env_dup[i]))) {
            i++;
            if (shell->env_dup[i] == NULL)
                break;
        }
        new_env[new_index] = shell->env_dup[i];
    }
    new_env[new_index] = NULL;
    new_env[new_index + 1] = NULL;
    return (new_env);
}

char **fill_env(char **dup_env, char *name, char *value, shell_t *shell)
{
    int index = get_indexes(shell->env_dup);
    int i = 0;
    int skip = 0;

    for (; i != index; i++) {
        if (!my_strcmp(get_name(shell->env_dup[i]), name)) {
            dup_env[i] = my_strcat_env(name, value);
            skip = 1;
        } else
            dup_env[i] = shell->env_dup[i];
    }
    if (skip == 1) {
        dup_env[i] = NULL;
        return (dup_env);
    }
    dup_env[i] = my_strcat_env(name, value);
    dup_env[i + 1] = NULL;
    return (dup_env);
}

void my_exit(char **args, shell_t *shell)
{
    int exit_value = get_exit_value(args[1], shell);

    if (args[1] == NULL) {
        fill_history_file(shell->history, shell->env_dup, shell);
        exit(exit_value);
    }
    if (args[2] != NULL)
        return;
    fill_history_file(shell->history, shell->env_dup, shell);
    free(args[0]);
    free(args[1]);
    free_shell(shell);
    exit(exit_value);
}
