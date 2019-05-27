/*
** EPITECH PROJECT, 2019
** 42sh.c
** File description:
** alias.
*/

#include "mysh.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>

char *check_name_alias(char ***tab, int index)
{
    int dbl_str = 0;

    for (int c = 0; tab[c] != NULL; c++) {
        if (tab[index][0] != NULL && tab[c][0] != NULL &&
            strcmp(tab[index][0], tab[c][0]) == 0 &&
            dbl_str == 0 && index == c)
            dbl_str++;
        else if (tab[index][0] != NULL && tab[c][0] != NULL &&
                strcmp(tab[index][0], tab[c][0]) == 0)
            return (NULL);
    }
    return (tab[index][0]);
}

char *get_value_alias(char *alias)
{
    int quote = 0;
    int j = 0;
    char *value = calloc(1, strlen(alias));

    for (int i = 0; alias[i] != '\0'; i++) {
        if (alias[i] == 39) {
            quote++;
            i++;
        }
        if (quote == 1) {
            value[j] = alias[i];
            j++;
        }
    }
    return (value);
}

char *get_name_alias(char *alias)
{
    int i = 0;
    char space[strlen(alias)];
    char *name = calloc(1, strlen(alias));

    for (; alias[i] != ' '; i++) {
        if (alias[i] == '\0') {
            free(name);
            return (NULL);
        }
        space[i] = alias[i];
    }
    space[i] = '\0';
    if (strcmp(space, "alias") != 0)
        return (NULL);
    for (int j = 0; alias[i + 1] != '='; i++, j++) {
        if (alias[i + 1] == '\0' || alias[i + 1] == 39)
            return (NULL);
        name[j] = alias[i + 1];
    }
    return (name);
}

char ***get_tab(char **alias, int index)
{
    char ***tab = malloc(sizeof(char **) * (index + 1));
    int z = 0;

    if (tab == NULL)
        return (NULL);
    for (; z != index; z++) {
        tab[z] = malloc(sizeof(char *) * 3);
        if (tab[z] == NULL)
            return (NULL);
    }
    tab[z] = NULL;
    for (int i = 0; alias[i] != NULL; i++) {
        tab[i][0] = get_name_alias(alias[i]);
        tab[i][1] = get_value_alias(alias[i]);
    }
    for (int i = 0; tab[i] != NULL; i++)
        tab[i][0] = check_name_alias(tab, i);
    free_tab(alias);
    return (tab);
}

char ***open_alias(char *path)
{
    FILE *fd = 0;
    int i = 0;
    char **alias = malloc(sizeof(char *) * 1);
    char *buf = NULL;
    size_t len;

    fd = fopen(path, "r");
    if (fd == NULL)
        return (NULL);
    for (; getline(&buf, &len, fd) != -1; i++) {
        alias[i] = strdup(buf);
        alias = realloc(alias, sizeof(char *) * (i + 2));
        free(buf);
        buf = NULL;
    }
    fclose(fd);
    alias[i] = NULL;
    return (get_tab(alias, i));
}
