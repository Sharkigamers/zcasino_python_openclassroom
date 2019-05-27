/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** and_or
*/

#include "mysh.h"
#include "tree.h"

static int and_or_fction(shell_t *shell, tree_t *tree)
{
    static int last = 0;

    if (shell->doors == 2 && shell->return_value != 0 && last != 1)
        shell->doors = 4;
    if (shell->doors == 3 && shell->return_value == 0 && last != 1)
        shell->doors = 5;
    if (last == 3 && shell->doors == 4 && shell->return_value != 0) {
        shell->doors = 3;
        return (0);
    }
    last = tree->separator_type;
    if (shell->doors == 4 || shell->doors == 5)
        return (1);
    if (tree->separator_type == 2)
        shell->doors = 2;
    if (tree->separator_type == 3)
        shell->doors = 3;
    return (0);
}

int doors_and_or(shell_t *shell, tree_t *tree)
{
    if (and_or_fction(shell, tree) == 1) {
        if (tree->separator_type == 1) {
            shell->doors = 0;
        }
        return (1);
    }
    return (0);
}
