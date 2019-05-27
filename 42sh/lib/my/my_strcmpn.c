/*
** EPITECH PROJECT, 2019
** my_strcmpn
** File description:
** compare n chars in a string
*/

#include "mysh.h"

#include <stddef.h>

int my_strcmpn(char *const str, char *const cmp, int n)
{
    if (str == NULL || cmp == NULL || n <= 0)
        return (-1);
    for (int i = 0; i != n ; i++) {
        if (str[i] != cmp[i])
            return (1);
    }
    return (0);
}
