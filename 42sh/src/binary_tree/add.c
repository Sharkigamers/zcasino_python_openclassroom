/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** add things
*/

#include "tree.h"
#include "mysh.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

int *handle_sep_index(int *sep_index, int sep, int reset)
{
    static int sep_size = 0;

    if (reset == 1)
        sep_size = 0;
    else {
        sep_index[sep_size] = sep;
        sep_size++;
    }
    return (sep_index);
}

int add_left(tree_t *tree, char *line, int sep_type)
{
    tree->left = malloc(sizeof(tree_t));
    if (tree->left == NULL)
        exit(84);
    return (0);
}

tree_t *create_node(void)
{
    tree_t *node = malloc(sizeof(tree_t));

    if (node == NULL)
        exit(84);
    node->left = NULL;
    node->line = NULL;
    node->redir_type = 0;
    node->separator_type = 0;
    return (node);
}

int add_current(tree_t *tree, char *line, int sep_type)
{
    tree->line = my_strclean(strdup(line));
    tree->redir_type = 0;
    tree->separator_type = sep_type;
    tree->left = NULL;
    return (0);
}

tree_t **simple_node(tree_t **node, char *line, int type)
{
    node[0]->line = line;
    node[0]->redir_type = type;
    node[0]->separator_type = 0;
    node[0]->right = NULL;
    node[0]->left = NULL;
    return (node);
}
