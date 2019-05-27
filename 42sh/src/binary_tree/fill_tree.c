/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** ui
*/

#include "tree.h"
#include "mysh.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

int check_redir(char *line, int i)
{
    if (i > 0 && line[i - 1] != '>' && line[i] == '>' && line[i + 1] != '>')
        return (1);
    if (i > 0 && line[i - 1] != '>' && line[i] == '>' && line[i + 1] == '>')
        return (2);
    if (i > 0 && line[i - 1] != '<' && line[i] == '<' && line[i + 1] != '<')
        return (3);
    if (i > 0 && line[i - 1] != '<' && line[i] == '<' && line[i + 1] == '<')
        return (4);
    return (0);
}

int is_a_redirection(char *line)
{
    int type = 0;

    for (int i = 0; line[i] != '\0'; i++) {
        type += check_redir(line, i);
    }
    if (type > 4)
        return (5);
    return (type);
}

static char *get_command(char *line)
{
    int index[] = {0, 0, 0};
    char *res = calloc(1, sizeof(char) * (strlen(line) + 1));
    int redi = 0;
    int is_space_after = 0;
    if (res == NULL)
        exit(84);
    if (is_a_redirection(line) == 5)
        return (strdup(line));
    for (; line[index[0]] != '\0'; index[0]++) {
        redi = check_redir(line, index[0]);
        if (redi != 0) {
            index[2] = 1;
            is_space_after = (line[index[0] + 1] == ' ' ? 2 : 1);
            index[0] += ((redi == 2 || redi == 4) ? 1 : 0);
        }
        if (index[2] == 0 || is_space_after < 0)
            res[index[1]++] = line[index[0]];
        is_space_after -= (line[index[0]] == ' ' ? 1 : 0);
    }
    return (res);
}

char *get_redir_name(char *line)
{
    int index[] = {0, 0, 0};
    char *res = calloc(1, sizeof(char) * (strlen(line) + 1));
    int redi = 0;
    int is_space_after = 0;

    if (res == NULL)
        exit(84);
    for (; line[index[0]] != '\0'; index[0]++) {
        redi = check_redir(line, index[0]);
        if (redi != 0) {
            index[2] = 1;
            index[0] += ((redi == 2 || redi == 4) ? 1 : 0);
            is_space_after = (line[index[0] + 1] == ' ' ? 2 : 1);
        } else if (index[2] == 1 && is_space_after > 0)
            res[index[1]++] = line[index[0]];
        is_space_after -= (line[index[0]] == ' ' ? 1 : 0);
    }
    return (my_strclean(res));
}

int manage_tree(tree_t *tree, char **expr, int *separators)
{
    char *command = NULL;
    char *redir_name = NULL;
    int is_redir = 0;

    for (int i = 0; expr[i] != NULL; i++) {
        is_redir = is_a_redirection(expr[i]);
        if (is_redir != 0) {
            command = get_command(expr[i]);
            redir_name = get_redir_name(expr[i]);
            tree->right = add_right(redir_name, is_redir);
            add_current(tree, command, separators[i]);
        } else {
            add_current(tree, expr[i], separators[i]);
        }
        tree->left = create_node();
        tree = tree->left;
        tree->left = NULL;
        tree->right = NULL;
    }
    return (0);
}
