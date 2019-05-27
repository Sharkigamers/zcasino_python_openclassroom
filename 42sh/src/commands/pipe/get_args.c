/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** abc
*/

#include "mysh.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

char ***get_arguments(char **strings)
{
    int index = get_indexes(strings);
    char ***args = malloc(sizeof(char **) * (index * 2));
    int i = 0;

    if (args == NULL)
        exit(84);
    for (; strings[i] != NULL; i++)
        args[i] = get_args(strings[i]);
    args[i] = NULL;
    return (args);
}

static int get_nb_pipe(char *line)
{
    int count = 0;

    for (int i = 0; line[i] != '\0'; i++)
        count += (line[i] == '|' ? 1 : 0);
    return (count);
}

static char **get_tab(char *line)
{
    int nb_pipe = get_nb_pipe(line);
    char **tab = malloc(sizeof(char *) * (nb_pipe + 2));

    if (tab == NULL)
        exit(84);
    for (int i = 0; i != nb_pipe + 1; i++) {
        tab[i] = calloc(1, sizeof(char) * (strlen(line) + 1));
        if (tab[i] == NULL)
            exit(84);
    }
    tab[nb_pipe + 1] = NULL;
    return (tab);
}

char **setup_commands(char *line)
{
    int index[] = {0, 0};
    char **tab = get_tab(line);

    if (tab == NULL)
        exit(84);
    for (int i = 0; line[i] != '\0'; i++, index[1]++) {
        if (line[i] == '|') {
            index[0]++;
            index[1] = -1;
        } else
            tab[index[0]][index[1]] = line[i];
    }
    for (int i = 0; tab[i] != NULL; i++)
        tab[i] = my_strclean(tab[i]);
    return (tab);
}
