/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** echo lol
*/

#include "mysh.h"

#include <stdlib.h>
#include <stddef.h>

static void print_line(char *str)
{
    int i = 0;

    for (; str[i] != '='; i++);
    i++;
    for (; str[i] != '\0'; i++) {
        my_putchar(str[i]);
    }
}

static char *get_index_from_str(char *str)
{
    char *index = calloc(1, sizeof(char) * my_strlen(str));
    int j = 0;

    if (index == NULL)
        exit(84);
    for (int i = 1; i != my_strlen(str); i++, j++)
        index[j] = str[i];
    index[j] = '\0';
    return (index);
}

static int get_env_index_from_str(char *str, shell_t *shell)
{
    char *index = get_index_from_str(str);
    int env_index = 0;

    for (; shell->env_dup[env_index] != NULL; env_index++) {
        if (!my_strcmpn(shell->env_dup[env_index], index, my_strlen(index)))
            return (env_index);
    }
    return (-1);
}

static int check_env(int i, char *str, shell_t *shell)
{
    int index = get_env_index_from_str(str, shell);

    if (str[i] == '?') {
        my_printf("%i", shell->return_value);
        shell->return_value = 0;
    } else if (index != -1)
        print_line(shell->env_dup[index]);
    else {
        my_putstr_err(str);
        my_putstr_err(": Undefined variable.");
        shell->return_value = 1;
    }
    return (0);
}

int my_echo(shell_t *shell, char **args)
{
    for (int i = 1; args[i] != NULL; i++) {
        for (int j = 0; args[i][j] != '\0'; j++)
            if (args[i][j] == '$') {
                check_env(i, args[i], shell);
                break;
            }
            else
                my_putchar(args[i][j]);
        if (args[i + 1] != NULL)
            my_putchar(' ');
    }
    my_putchar('\n');
    return (0);
}
