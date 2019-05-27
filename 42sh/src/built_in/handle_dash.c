/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** abc
*/

#include "mysh.h"

#include <stddef.h>
#include <stdlib.h>

char *get_env_value(char **env, int index)
{
    char *res = calloc(1, sizeof(char) * my_strlen(env[index]));
    int count = 7;

    if (res == NULL)
        return NULL;
    for (int i = 0; count != my_strlen(env[index]); i++, count++)
        res[i] = env[index][count];
    return res;
}

char *find_old_pwd(shell_t *shell)
{
    char *res = NULL;

    for (int i = 0; shell->env_dup[i] != NULL; i++) {
        if (!my_strcmp(get_name(shell->env_dup[i]), "OLDPWD"))
            res = get_env_value(shell->env_dup, i);
    }
    return res;
}
