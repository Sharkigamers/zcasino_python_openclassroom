/*
** EPITECH PROJECT, 2019
** err_backchar.c
** File description:
** err_backchar.
*/

#include "mysh.h"
#include <stdlib.h>
#include <stdio.h>

int space_is_inhibitor(char *line)
{
    for (int i = 0; line[i] != '\0'; i++)
        if (line[i] == '\\' && line[i + 1] != '\0')
            if (line[i] == '\\' && line[i + 1] == ' ')
                return (0);
    return (1);
}

static char rtn_back_char(shell_t *shell)
{
    for (int i = 0; shell->base_line[i] != '\0'; i++)
        if (shell->base_line[i] == '"' || shell->base_line[i] == '\'')
            return (shell->base_line[i]);
}

int error_backchar(shell_t *shell)
{
    int count = 0;
    char chara;

    for (int i = 0; shell->base_line[i] != '\0'; i++)
        shell->base_line[i] == '"' || shell->base_line[i] == '\'' ?
        count++ : 0;
    count > 0 ? chara = rtn_back_char(shell) : 0;
    if (count % 2 == 1) {
        dprintf(2, "Unmatched \'%c\'.\n", chara);
        shell->return_value = 1;
        return (1);
    }
    return (0);
}
