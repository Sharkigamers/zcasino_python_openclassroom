/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** annex_function
*/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#include "mysh.h"

static void last_cond(char **tab, int index, int count, int semis)
{
    tab[index][count] = '\0';
    for (int i = 0; i <= semis; i++)
        tab[i] = my_strclean(tab[i]);
    tab[index + 1] = NULL;
}

char **get_commands_from_input(char *line, shell_t *shell)
{
    int semis = get_semis(line);
    char **tab = malloc(sizeof(char *) * (semis + 2));
    int index = 0;
    int count = 0;

    if (tab == NULL)
        exit(84);
    shell->command_lenght = semis + 1;
    for (int i = 0; i != semis + 1; i++)
        tab[i] = calloc(1, sizeof(char) * my_strlen(line) + 1);
    for (int i = 0; line[i] != '\0'; i++, count++) {
        if (line[i] == ';') {
            tab[index][count] = '\0';
            index++;
            count = -1;
        } else
            tab[index][count] = line[i];
    }
    last_cond(tab, index, count, semis);
    return (tab);
}
