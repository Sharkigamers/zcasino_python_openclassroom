/*
** EPITECH PROJECT, 2019
** my_strcat_space.c
** File description:
** my_strcat.
*/

#include "mysh.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *my_strcat_with_space(char *dest, char const *src)
{
    int dest_len = strlen(dest);
    int src_len = strlen(src);
    char *result = calloc(1, sizeof(char) * (dest_len + src_len) + 2);
    int count = 0;

    for (int i = 0; dest[i] != '\0'; i++, count++)
        result[i] = dest[i];
    result[count] = ' ';
    count++;
    for (int j = 0; src[j] != '\0'; j++, count++)
        result[count] = src[j];
    result[count] = '\0';
    return (result);
}
