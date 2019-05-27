/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** basic_searching
*/

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "mysh.h"

static char *fill_by_args(char *str, char **args)
{
    char *new_str = NULL;
    int nb_char = 0;
    int k = 0;

    for (int i = 1; args[i] != NULL; i++)
        for (int j = 0; args[i][j] != '\0'; j++, nb_char++);
    new_str = malloc(strlen(str) + nb_char + 1);
    if (new_str == NULL)
        exit(84);
    for (int i = 0; str[i] != '\0' && str[i] != '\n'; i++, k++)
        new_str[k] = str[i];
    new_str[k] = ' ';
    for (int i = 1; args[i] != NULL; i++, k++) {
        for (int j = 0; args[i][j] != '\0'; j++, k++)
            new_str[k + 1] = args[i][j];
        new_str[k + 1] = ' ';
    }
    new_str[k] = '\0';
    free(str);
    return (new_str);
}

static int gest_error(char **history, shell_t *shell, int pre_instru)
{
    int i = 0;

    for (i = 0; history[i] != NULL; i++);
    i -= pre_instru;
    if (i <= shell->history_pointer) {
        my_printf("%d", i / 2 + 1);
        my_putstr_err(": Event not found.\n");
        shell->return_value = 1;
        return (-84);
    }
    return (i);
}

static void gest_tabs(char **args, char *commands)
{
    for (int j = 0; args[j] != NULL; j++)
        free(args[j]);
    free(args);
    for (int k = 0; commands[k] != '\0'; k++)
        commands[k] == '\n' ? commands[k] = '\0' : 0;
}

static void refill_hist(char **history, int pre_instru, char *arged_line, int i)
{
    free(history[i + 2]);
    arged_line = realloc(arged_line, strlen(arged_line) + 2);
    arged_line[strlen(arged_line) + 1] = '\0';
    arged_line[strlen(arged_line)] = '\n';
    history[i + 2] = strdup(arged_line);
    free(arged_line);
}

void last_hist(char **args, char **history, shell_t *shell, int pre_instru)
{
    int i = 0;
    tree_t *tree = NULL;
    char *arged_line = NULL;

    i = gest_error(history, shell, pre_instru);
    if (i == -84)
        return;
    arged_line = strdup(history[i]);
    arged_line = fill_by_args(arged_line, args);
    my_printf("%s\n", arged_line);
    tree = create_tree_from_input(arged_line);
    gest_tabs(args, tree->line);
    if (shell->detect_free == 1)
        refill_hist(history, pre_instru, arged_line, i);
    list_functions(tree, args, shell);
    shell->return_value = 0;
}
