/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** handle all binary tree's mallocs
*/

#include "tree.h"

#include <stdlib.h>
#include <string.h>
#include <stddef.h>

static int get_sep_count(char *line)
{
    int count = 0;

    for (int i = 0; line[i] != '\0'; i++) {
        if (is_a_separator(line, i))
            count++;
    }
    return (count);
}

char **get_expr_tab(char *line)
{
    int count = get_sep_count(line);
    char **expr = malloc(sizeof(char *) * (count + 2));

    if (expr == NULL)
        exit(84);
    for (int i = 0; i != count + 1; i++) {
        expr[i] = calloc(1, sizeof(char) * (strlen(line) + 1));
        if (expr[i] == NULL)
            exit(84);
    }
    return (expr);
}

char *replace_sign(char *line)
{
    char *res = calloc(1, sizeof(char) * (strlen(line)));
    int count = 0;

    if (res == NULL)
        exit(84);
    for (int i = 1; line[i] != '\0'; i++, count++)
        res[count] = line[i];
    free(line);
    return (res);
}
