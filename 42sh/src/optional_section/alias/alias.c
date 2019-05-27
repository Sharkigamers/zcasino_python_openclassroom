/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** fill the alias file.
*/

#include "mysh.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char *get_alias_path(void)
{
    char *path = my_strcat(get_pwd(), ".42_alias");

    return (path);
}

void print(FILE *fd, char **args)
{
    fprintf(fd, "alias %s='", args[1]);
    for (int i = 0; args[i] != NULL; i++) {
        if (i >= 2 && args[i + 1] == NULL)
            fprintf(fd, "%s", args[i]);
        else if (i >= 2)
            fprintf(fd, "%s ", args[i]);
    }
    fprintf(fd, "'\n");
    fclose(fd);
}

static int get_tab_length(char **args)
{
    int count = 0;

    for (; args[count] != NULL; count++);
    return (count);
}

static int print_alias(FILE *fd)
{
    char *buf = NULL;
    size_t len = 0;

    while (getline(&buf, &len, fd) != -1) {
        printf("%s", buf);
        free(buf);
        buf = NULL;
    }
    free(buf);
    fclose(fd);
    return (0);
}

void my_alias(shell_t *shell, char **args)
{
    FILE *fd = NULL;
    int count = get_tab_length(args);

    fd = fopen(shell->alias_path, "a+");
    if (fd == NULL)
        return;
    if (count == 1) {
        print_alias(fd);
        return;
    } else if (count == 2)
        return;
    else
        print(fd, args);
}
