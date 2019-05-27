/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** setup separator list
*/

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "tree.h"
#include "mysh.h"

static int get_tree_length(tree_t *tree)
{
    int count = 0;

    if (tree == NULL)
        return (0);
    for (; tree->left != NULL; tree = tree->left, count++);
    return (count);
}

int *setup_sep_list(tree_t *tree)
{
    int list_length = get_tree_length(tree);
    int *list = calloc(1, sizeof(int) * (list_length + 1));

    if (list == NULL)
        exit(84);
    if (tree == NULL) {
        free(list);
        return (NULL);
    }
    for (int i = 0; tree->left != NULL; tree = tree->left, i++)
        list[i] = tree->separator_type;
    return (list);
}
