/*
** EPITECH PROJECT, 2018
** my_strcmp.c
** File description:
** compare 2 strings
*/

#include "mysh.h"

#include <stddef.h>

int my_strcmp(char *const str, char *const cmp)
{
    if (str == NULL || cmp == NULL)
        return (-1);
    if (my_strlen(str) != my_strlen(cmp))
        return (1);
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != cmp[i])
            return (1);
    }
    return (0);
}

int my_stricmp(char *const str, char *const cmp, int i)
{
    if (str == NULL || cmp == NULL)
        return (-1);
    for (int k = 0; str[i] != '\0'; i++, k++) {
        if (str[i] != cmp[k])
            return (1);
    }
    return (0);
}
