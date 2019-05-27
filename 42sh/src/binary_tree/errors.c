/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** oui pk pa
*/

#include "mysh.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

static int print_error_redir(int redirs[])
{
    if (redirs[0] > 1) {
        my_putstr_err("Ambiguous output redirect.\n");
        return (1);
    } else if (redirs[1] > 1) {
        my_putstr_err("Ambiguous intput redirect.\n");
        return (1);
    }
    return (0);
}

static int check_ambigous_separators(char *line, int i)
{
    if (line[i] == '&' && line[i + 1] == '|')
        return (1);
    if (line[i] == '&' && line[i + 1] == '&')
        return (1);
    if (line[i] == '|' && line[i + 1] == '|')
        return (1);
    return (0);
}

static int check_ambigous_redirections(char *line)
{
    int redirs[] = {0, 0};

    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == '>' && line[i + 1] != '\0' && line[i + 1] == '>') {
            redirs[0]++;
            i++;
        } else if (line[i] == '>')
            redirs[0]++;
        if (line[i] == '<' && line[i + 1] != '\0' && line[i + 1] == '<') {
            redirs[1]++;
            i++;
        } else if (line[i] == '<')
            redirs[1]++;
    }
    return (print_error_redir(redirs));
}

int check_basic_errors(char *line)
{
    int i = 0;

    if (check_ambigous_redirections(line))
        return (1);
    for (; line[i] != '\0'; i++) {
        if (check_ambigous_separators(line, i)) {
            my_putstr_err("Invalid null command.\n");
            return (1);
        }
    }
    return (0);
}
