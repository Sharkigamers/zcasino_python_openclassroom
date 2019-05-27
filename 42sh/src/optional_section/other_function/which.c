/*
** EPITECH PROJECT, 2019
** 42sh.c
** File description:
** which_command.
*/

#include "mysh.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void check_path_which(shell_t *shell, char *bin)
{
    char *name = NULL;

    for (int i = 0; shell->path[i] != NULL; i++) {
        name = my_strcat(shell->path[i], bin);
        if (!access(name, X_OK))
            printf("%s\n", name);
    }
}

int check_alias_command_which(shell_t *shell, char *bin)
{
    FILE *fd = 0;
    char *buf = NULL;
    size_t len;

    fd = fopen(shell->alias_path, "r");
    if (fd == NULL)
        return (0);
    while (getline(&buf, &len, fd) != -1)
        if (!strcmp(bin, get_name_alias(strdup(buf)))) {
            printf("%s: \t aliased to %s\n", bin, get_value_alias(strdup(buf)));
            return (1);
        }
    fclose(fd);
}

int check_shell_command_which(char *bin)
{
    for (int i = 0; shell_command[i] != NULL; i++)
        if (!strcmp(shell_command[i], bin)) {
            printf("%s: shell built-in command.\n", bin);
            return (1);
        }
    return (0);
}

void my_which(shell_t *shell, char **args)
{
    if (args[1] == NULL) {
        shell->return_value = 1;
        my_putstr_err("which: Too few arguments.\n");
        return;
    }
    for (int i = 1; args[i] != NULL; i++) {
        if (check_alias_command_which(shell, args[i]) == 1)
            return;
        if (check_shell_command_which(args[i]) == 1)
            return;
        check_path_which(shell, args[i]);
    }
}
