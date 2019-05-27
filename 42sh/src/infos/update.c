/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** sample text
*/

#include "mysh.h"

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <unistd.h>

char *get_pwd(void)
{
    int index = 0;
    char *pwd = calloc(1, 1024);

    if (pwd == NULL)
        exit(84);
    pwd = getcwd(pwd, 1024);
    pwd = my_strcat(pwd, "/");
    return pwd;
}

void update_path(char *name, char *value, shell_t *shell)
{
    if (value == NULL) {
        free_tab(shell->path);
        shell->path = NULL;
        return;
    }
    if (!my_strcmp(name, "PATH"))
        fill_path(shell, shell->env_dup);
}

int update_env_by_str(shell_t *shell, char *name, char *value)
{
    char *args[] = {"setenv", name, value, NULL};

    for (int index = 0; shell->env_dup[index] != NULL; index++) {
        if (!my_strcmp(get_name(shell->env_dup[index]), name)) {
            shell->env_dup[index] = my_strcat_env(name, value);
            return 0;
        }
    }
    my_setenv(shell, args);
    return 1;
}
