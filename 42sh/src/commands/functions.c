/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** functions
*/

#include <stddef.h>
#include <stdlib.h>

#include "mysh.h"
#include "tree.h"

void execute_fonction(char **args, char *bin, shell_t *shell, tree_t *tree)
{
    if (!is_a_pipe(tree->line, shell, tree->right));
    else if (!functions(bin, shell, args, tree->right)) {
        if (!is_a_binary(bin, args, shell, tree->right) ||
            !is_valid_input(bin, shell, args, tree->right));
        else if (my_strlen(tree->line) > 0)
            print_error(bin, shell);
    }
}

static int init_vars(tree_t *tree, char ***args, shell_t *shell, char **bin)
{
    int new_str = 0;

    tree->line = check_aliases(tree->line, shell->alias_path);
    *bin = get_bin(tree->line);
    *args = get_args(tree->line);
    new_str = fill_new_string(*args, &tree->line, shell);
    if (new_str == 1) {
        free(*bin);
        for (int i = 0; (*args)[i] != NULL; i++)
            free((*args)[i]);
        free(*args);
        *bin = get_bin(tree->line);
        *args = get_args(tree->line);
    } if (check_is_ini(shell) == 1) {
        free_tab(*args);
        *args = get_args_inhibitor(tree->line);
    } if (new_str == 2)
        return (1);
    return (0);
}

int list_functions(tree_t *tree, char **args, shell_t *shell)
{
    if (tree == NULL) {
        shell->return_value = 0;
        return (0);
    }
    for (char *bin = NULL; tree->left != NULL; tree = tree->left) {
        tree->line = check_aliases(tree->line, shell->alias_path);
        bin = get_bin(tree->line);
        args = get_args(tree->line);
        if (check_is_ini(shell) == 1) {
            free_tab(args);
            args = get_args_inhibitor(tree->line);
        } if (init_vars(tree, &args, shell, &bin) == 1)
            continue;
        if (doors_and_or(shell, tree) == 1)
            continue;
        if (env_slashed(shell->env_dup, tree->line) == 1)
            continue;
        execute_fonction(args, bin, shell, tree);
    }
    return (0);
}
