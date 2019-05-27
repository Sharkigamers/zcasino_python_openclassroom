/*
** EPITECH PROJECT, 2019
** minishell1
** File description:
** setup shell struct
*/

#include "mysh.h"

#include <stdlib.h>
#include <stddef.h>

int get_indexes(char **env)
{
    int i = 0;

    if (env == NULL || env[0] == NULL)
        return (0);
    for (; env[i] != NULL; i++);
    return (i);
}

char **fill_tab(int path_index, char **env, char **tab)
{
    int count = 5;
    int i = 0;
    int j = 0;

    for (;count != my_strlen(env[path_index]); j++, count++) {
        tab[i][j] = env[path_index][count];
        if (env[path_index][count] == ':') {
            tab[i][j] = '/';
            tab[i][j+1] = '\0';
            j = -1;
            i++;
        }
    }
    tab[i][j] = '/';
    tab[i][j + 1] = '\0';
    return (tab);
}

char **alloc_tab(int path_index, int rows, char **env)
{
    char **tab = malloc(sizeof(char *) * rows + 10);

    if (tab == NULL)
        exit(84);
    for (int j = 0; j != rows; j++) {
        tab[j] = malloc(sizeof(char) * my_strlen(env[path_index]));
        if (tab[j] == NULL)
            exit(84);
    }
    tab[rows] = NULL;
    tab = fill_tab(path_index, env, tab);
    return (tab);
}

void fill_path(shell_t *shell, char **env)
{
    int path_index = 0;
    int i = 0;
    int rows = 0;

    for (; env[path_index] != NULL; path_index++) {
        if (env[path_index][0] == 'P' && env[path_index][1] == 'A')
            break;
        if (env[path_index + 1] == NULL)
            return;
    }
    for (; i != my_strlen(env[path_index]); i++)
        if (env[path_index][i] == ':')
            rows++;
    rows++;
    shell->path = alloc_tab(path_index, rows, env);
}

shell_t *get_struct(char **env)
{
    shell_t *shell = malloc(sizeof(shell_t));

    if (env == NULL || env[0] == NULL) {
        env = get_replacement_env(shell);
        shell->path = path_replacement();
    } else
        shell->skip = 0;
    shell->alias_path = get_alias_path();
    shell->b_envp = env;
    shell->env_dup = env;
    shell->return_value = 0;
    shell->dir_error = 0;
    shell->errno_value = 0;
    if (shell->skip == 0) {
        shell->home = get_home(env);
        fill_path(shell, env);
    }
    setup_basic_hist_var(shell);
    return (shell);
}
