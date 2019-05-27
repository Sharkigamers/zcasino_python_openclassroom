/*
** EPITECH PROJECT, 2019
** is_inibhitor.c
** File description:
** inhibitor.
*/

#include "mysh.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int ini_inhibitor(char *line)
{
    for (int i = 0; line[i] != '\0'; i++)
        if (line[i] == '\\' && line[i + 1] == '\0' && line[1] != '\0')
            return (1);
    return (0);
}

static char *rtn_inhibitor(char *line, char *str, size_t n)
{
    int ini = ini_inhibitor(line);

    if (ini == 1) {
        printf("? ");
        if (getline(&str, &n, stdin) != -1)
            return (line);
    }
        for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == '\\' && line[i + 1] != '\0')
            if (line[i] == '\\' && line[i + 1] == ' ' && line[i + 2] == '\0')
                return (line);
    }
    return (line);
}

static char *setup_inhibitor(char *line)
{
    int count = 0;
    char *str = NULL;
    size_t n = 32;

    for (int i = 0; line[i] != '\0'; i++) {
        if (line[0] == '\\' && line[1] == '\0') {
            printf("? ");
            if (getline(&str, &n, stdin) != -1) {
                str[strlen(str) - 1] = '\0';
                return (str);
            }
        }
    }
    return (rtn_inhibitor(line, str, n));
}

char *is_inhibitor(char *line)
{
    int count = 0;

    for (int i = 0; line[i] != '\0'; i++)
        if (line[i] == ' ')
            count++;
    for (int i = 0; line[i] != '\0'; i++) {
        if (count == 0)
            if (line[i] == '\"' || line[i] == '\'')
                return (line);
        if (check_inhibitor(line) == 84)
            return (line);
    }
    return (setup_inhibitor(line));
}
