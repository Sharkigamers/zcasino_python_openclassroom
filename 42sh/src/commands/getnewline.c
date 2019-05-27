/*
** EPITECH PROJECT, 2019
** minishell1
** File description:
** get and proces new line
*/

#include <time.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "mysh.h"

int get_spaces(char *line)
{
    int i = 0;
    int space = 0;

    for (; line[i] != '\0'; i++) {
        if (line[i] == ' ' && line[i + 1] != ' ' && line[i+1] != '\0')
            space++;
    }
    return (space);
}

char *get_bin(char *line)
{
    int i = 0;
    char *result = calloc(1, sizeof(char) * my_strlen(line) + 1);

    if (result == NULL)
        exit(84);
    for (; line[i] != '\0'; i++) {
        if (line[i] == ' ')
            break;
        result[i] = line[i];
    }
    result[i] = '\0';
    return (result);
}

char **get_args(char *line)
{
    int spaces = get_spaces(line);
    char *binary = get_bin(line);
    char **args = malloc_args(binary, line, spaces);
    int index[] = {0 , 0, 0};

    for (; line[index[2]] != '\0'; index[2]++, index[1]++) {
        if (line[index[2]] == ' ') {
            index[0]++;
            index[1] = -1;
        } else
            args[index[0]][index[1]] = line[index[2]];
    }
    args[index[0] + 1] = NULL;
    for (int i = 0; args[i] != NULL; i++) {
        args[i] = check_interrogation_point(args[i], binary);
        args[i] = check_hook(args[i], binary);
    }
    return (args);
}

char *getnewline(shell_t *shell)
{
    char *line = NULL;
    size_t len = 0;

    shell->n_read = getline(&line, &len, stdin);
    if (shell->n_read == -1) {
        my_putstr("exit\n");
        fill_history_file(shell->history, shell->env_dup, shell);
        free(shell->alias_path);
        exit(shell->return_value);
    }
    shell->doors = 0;
    fill_var_history(&shell->history, line);
    line = my_strclean(line);
    line[my_strlen(line) - 1] = '\0';
    shell->base_line = line;
    return (line);
}
