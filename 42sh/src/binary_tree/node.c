/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** handle right node
*/

#include "tree.h"
#include "mysh.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

static char **get_tab(char *line)
{
    char **tab = malloc(sizeof(char *) * 3);

    for (int i = 0; i != 2; i++) {
        tab[i] = calloc(1, sizeof(char) * (strlen(line) + 1));
        if (tab[i] == NULL)
            exit(84);
    }
    tab[2] = NULL;
    return (tab);
}

static char *remove_command(char *line)
{
    char *res = my_strclean(strdup(line));
    int count = 0;
    int space = 0;

    for (int i = 0; line[i] != '\0'; i++) {
        if (check_redir(line, i) != 0 && space == 0)
            space = 1;
        if (space == 1)
            res[count++] = line[i];
    }
    return (res);
}

static char **get_redir_tab(char *line)
{
    char *new_line = remove_command(line);
    char **tab = get_tab(line);
    int index[] = {0, 0, 0};

    for (int i = 0; new_line[i] != '\0'; i++, index[1]++) {
        if (i != 0 && check_redir(new_line, i + 1) != 0 && !index[2]) {
            index[0]++;
            index[1] = -1;
            index[2] = 1;
        } else
            tab[index[0]][index[1]] = new_line[i];
    }
    tab[0] = my_strclean(tab[0]);
    tab[1] = my_strclean(tab[1]);
    return (tab);
}

tree_t **double_node(tree_t **node, char **args)
{
    for (int i = 0; i != 2; i++) {
        node[i]->line = get_redir_name(args[i]);
        node[i]->redir_type = check_redir(args[i], 0);
        node[i]->right = NULL;
        node[i]->left = NULL;
        node[i]->separator_type = 0;
    }
    return (node);
}

tree_t **add_right(char *line, int type)
{
    tree_t **node = malloc(sizeof(tree_t *) * 2);
    char **args = get_redir_tab(line);

    if (node == NULL)
        exit(84);
    for (int i = 0; i != 2; i++) {
        node[i] = malloc(sizeof(tree_t));
        if (node[i] == NULL)
            exit(84);
    }
    if (args[1] == NULL || args == NULL || !is_a_redirection(line))
        return (simple_node(node, line, type));
    else
        return (double_node(node, args));
}
