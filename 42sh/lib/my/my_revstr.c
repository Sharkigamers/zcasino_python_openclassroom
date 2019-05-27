/*
** EPITECH PROJECT, 2018
** my_revstr.c
** File description:
** reverse a string
*/

#include "mysh.h"

#include <stdio.h>
#include <stdlib.h>

char *my_revstr(char *str)
{
    char *new = calloc(1, sizeof(char) * my_strlen(str) + 1);
    int j = 0;

    for (int i = my_strlen(str) - 1; i >= 0; i--, j++)
        new[j] = str[i];
    return (new);
}

