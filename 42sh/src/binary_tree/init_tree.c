/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** create tree
*/

#include "tree.h"
#include "mysh.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

inline int is_a_separator(char *line, int index)
{
    if (line[index] == ';')
        return (1);
    if (line[index + 1] != '\0' && line[index] == '&' &&
        line[index + 1] == '&')
        return (2);
    if (line[index + 1] != '\0' && line[index] == '|' &&
        line[index + 1] == '|')
        return (3);
    return (0);
}

static int get_sep_count(char *line)
{
    int count = 0;

    for (int i = 0; line[i] != '\0'; i++) {
        if (is_a_separator(line, i))
            count++;
    }
    return (count);
}

static char **get_expr(char *line, int **sep_index)
{
    char **expr = get_expr_tab(line);
    int index[] = {0, 0, 0};
    int sep = 0;

    for (; line[index[2]] != '\0'; index[2]++, index[1]++) {
        sep = is_a_separator(line, index[2]);
        if (sep == 1) {
            index[0]++;
            index[1] = -1;
            *sep_index = handle_sep_index(*sep_index, sep, 0);
        } else if (sep == 2 || sep == 3) {
            index[0]++;
            index[1] = -1;
            index[2]++;
            *sep_index = handle_sep_index(*sep_index, sep, 0);
        } else
            expr[index[0]][index[1]] = line[index[2]];
    }
    expr[index[0] + 1] = NULL;
    return (expr);
}

static int fill_tree(tree_t *tree, char *line)
{
    int errors = 0;
    char **expr = {NULL};
    int *sep_index = calloc(1, sizeof(int) * (get_sep_count(line) + 1));

    if (sep_index == NULL)
        exit(84);
    expr = get_expr(line, &sep_index);
    for (int i = 0; expr[i] != NULL; i++) {
        if (check_basic_errors(expr[i]))
            return (0);
        expr[i] = my_strclean(expr[i]);
    }
    manage_tree(tree, expr, sep_index);
    sep_index = handle_sep_index(sep_index, 0, 1);
    free(sep_index);
    return (0);
}

tree_t *create_tree_from_input(char *line)
{
    tree_t *tree = malloc(sizeof(tree_t));

    if (tree == NULL)
        exit(84);
    tree->left = NULL;
    tree->right = NULL;
    if (line == NULL || line[0] == '\0' || check_basic_errors(line)) {
        free(tree);
        return (NULL);
    }
    fill_tree(tree, line);
    return (tree);
}
