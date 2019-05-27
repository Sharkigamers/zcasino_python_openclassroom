/*
** EPITECH PROJECT, 2019
** 42sh.c
** File description:
** where.
*/

#include "mysh.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void check_path_where(shell_t *shell, char *bin)
{
    char *name = NULL;

    for (int i = 0; shell->path[i] != NULL; i++) {
        name = my_strcat(shell->path[i], bin);
        if (!access(name, X_OK)) {
            printf("%s\n", name);
        }
    }
}

void check_alias_command_where(shell_t *shell, char *bin)
{
    FILE *fd = 0;
    char *buf = NULL;
    size_t len;

    fd = fopen(shell->alias_path, "r");
    if (fd == NULL)
        return;
    for (; getline(&buf, &len, fd) != -1;)
        if (!strcmp(bin, get_name_alias(strdup(buf))))
            printf("%s is aliased to %s\n", bin, get_value_alias(strdup(buf)));
    fclose(fd);
}

void check_shell_command_where(char *bin)
{
    for (int i = 0; shell_command[i] != NULL; i++)
        if (!strcmp(shell_command[i], bin))
            printf("%s is a shell built-in\n", bin);
}

void my_where(shell_t *shell, char **args)
{
    if (args[1] == NULL) {
        shell->return_value = 1;
        my_putstr_err("where: Too few arguments.\n");
        return;
    }
    for (int i = 1; args[i] != NULL; i++) {
        check_alias_command_where(shell, args[i]);
        check_shell_command_where(args[i]);
        check_path_where(shell, args[i]);
    }
}
