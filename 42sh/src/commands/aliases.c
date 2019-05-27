/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** check aliases
*/

#include "mysh.h"

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

static char *get_past_bin(char *str)
{
    char *new_str = calloc(1, sizeof(char) * my_strlen(str));
    int lenght = my_strlen(get_bin(str));

    for (int i = 0; str[lenght] != '\0'; i++, lenght++)
        new_str[i] = str[lenght];
    return (new_str);
}

char *check_aliases(char *str, char *path)
{
    char *new_str = get_past_bin(str);
    char ***aliases = open_alias(path);

    if (aliases == NULL)
        return (str);
    for (int i = 0; aliases[i] != NULL; i++) {
        if (aliases[i][0] == NULL);
        else if (!strcmp(aliases[i][0], get_bin(str))) {
            return (my_strcat(aliases[i][1], new_str));
        }
    }
    if (aliases == NULL)
        return (str);
    for (int i = 0; aliases[i] != NULL; i++) {
        for (int y = 0; y != 2; y++)
            free(aliases[i][y]);
        free(aliases[i]);
    }
    free (aliases);
    return (str);
}
