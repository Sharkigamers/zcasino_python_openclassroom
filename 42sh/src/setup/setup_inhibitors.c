/*
** EPITECH PROJECT, 2019
** setup_inhibitor.c
** File description:
** setup_inhibitor.
*/

#include "mysh.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int *get_args_setup2(int *index, char *line)
{
    if (line[index[2]] == '\\' && line[index[2] + 1] == '"'
    || line[index[2]] == '\\' && line[index[2] + 1] == '\'') {
        index[2]++;
        index[4] = 1;
    }
    if (line[index[2]] == '"' && index[4] != 1 ||
    line[index[2]] == '\'' && index[4] != 1 ||
    line[index[2]] == '\\' && line[index[2] + 1] == ' ') {
        index[3]++;
        index[2]++;
        index[4] = 0;
    }
    return (index);
}

static int *get_args_setup(int *index, char *line)
{
    index[2] += (line[index[2]] == '\\' && line[index[2] + 1] != '\\' &&
    line[index[2] + 1] != ' ') ? 1 : 0;
    if (line[index[2]] == '"' && line[index[2] + 1] == '\\' ||
    line[index[2]] == '\\' ||
    line[index[2]] == '\'' && line[index[2] + 1] == '\\') {
        index[2]++;
        index[4] = 1;
    }
    if (index[2] > 0)
        if (line[index[2] - 1] != '\\' && line[index[2]] == '"'
        || line[index[2] - 1] != '\\' && line[index[2]] == '\'') {
            index[2]++;
            index[4] = 1;
        }
    return (get_args_setup2(index, line));
}

char **get_args_inhibitor(char *line)
{
    int spaces = get_spaces(line);
    char *binary = get_bin(line);
    char **args = malloc_args(binary, line, spaces);
    int *index = calloc(1, sizeof(int) * 1500);

    if (index == NULL)
        exit(84);
    for (; line[index[2]] != '\0'; index[2]++, index[1]++) {
        index = get_args_setup(index, line);
        (line[index[2]] == '\\' && line[index[2] + 1] != ' ' &&
        line[index[2] + 1] == '\\') ? index[2]++ : 0;
        if (line[index[2]] == ' ' && index[3] % 2 == 0) {
            index[0]++;
            index[1] = -1;
        } else
            args[index[0]][index[1]] = line[index[2]];
    }
    args[index[0] + 1] = NULL;
    free(index);
    return (args);
}

int check_inhibitor(char *line)
{
    int count = 1;

    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == '\\' && i != 0)
            if (line[i - 1] == '\\')
            count++;
    }
    if (count % 2 == 0)
        return (84);
    return (0);
}
