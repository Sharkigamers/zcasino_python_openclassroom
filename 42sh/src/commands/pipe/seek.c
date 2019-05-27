/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** seek commands
*/

#include <stdlib.h>

#include "mysh.h"

int seek_command(char *string, char **args, shell_t *shell, tree_t **right)
{
    char *bin = get_bin(string);

    if (!functions(bin, shell, args, right)) {
        if (!is_a_binary(bin, args, shell, right) ||
            !is_valid_input(bin, shell, args, right));
        else if (my_strlen(string) > 0)
            print_error(bin, shell);
    }
    exit(shell->return_value);
}
