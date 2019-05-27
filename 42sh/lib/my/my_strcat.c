/*
** EPITECH PROJECT, 2019
** minishell1
** File description:
** concat 2 strings
*/

#include "mysh.h"

#include <stdlib.h>

char *my_strncat(char *dest, char const *src, int i)
{
    int dest_len = my_strlen(dest);
    int src_len = my_strlen(src);
    char *result = calloc(1, sizeof(char) * (dest_len + src_len) + 1 - i);
    int count = 0;

    for (; dest[i] != '\0'; i++, count++)
        result[count] = dest[i];
    for (int j = 0; src[j] != '\0'; j++, count++)
        result[count] = src[j];
    result[count] = '\0';
    return (result);
}

char *my_strcat(char *dest, char const *src)
{
    int dest_len = my_strlen(dest);
    int src_len = my_strlen(src);
    char *result = calloc(1, sizeof(char) * (dest_len + src_len) + 1);
    int count = 0;
    int i = 0;

    for (; dest[i] != '\0'; i++, count++)
        result[i] = dest[i];
    for (int j = 0; src[j] != '\0'; j++, count++)
        result[count] = src[j];
    result[count] = '\0';
    return (result);
}

char *my_strcat_env(char *dest, char const *src)
{
    int dest_len = my_strlen(dest);
    int src_len = my_strlen(src);
    char *result = calloc(1, sizeof(char) * (dest_len + src_len) * 2);
    int count = 0;
    int i = 0;

    for (; dest[i] != '\0'; i++, count++)
        result[i] = dest[i];
    result[i] = '=';
    count++;
    for (int j = 0; src[j] != '\0'; j++, count++)
        result[count] = src[j];
    result[count] = '\0';
    return (result);
}
