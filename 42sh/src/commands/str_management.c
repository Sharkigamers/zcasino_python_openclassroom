/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** handle string operations
*/

#include "mysh.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *cut_str(char *str, char delim)
{
    char *res = calloc(1, sizeof(char) * strlen(str) + 1);
    int count = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == delim)
            break;
        res[i] = str[i];
    }
    return (res);
}

char *get_value(char *str, char delim)
{
    char *res = calloc(1, sizeof(char) * strlen(str));
    int count = 0;
    int print = 0;

    if (res == NULL)
        exit(84);
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == delim && !print)
            print = 1;
        else if (print == 1) {
            res[count] = str[i];
            count++;
        }
    }
    return (res);
}
