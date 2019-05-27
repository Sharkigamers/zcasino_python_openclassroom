/*
** EPITECH PROJECT, 2019
** minishell1
** File description:
** exec functions
*/

#include "mysh.h"
#include "tree.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

static void print_log_name(char **env)
{
    for (int i = 0; env[i] != NULL; i++) {
        if (!my_strcmpn(env[i], "LOGNAME", 7)) {
            for (int j = 8; env[i][j] != '\0'; j++)
                my_putchar(env[i][j]);
            return;
        }
    }
    my_putstr("Unknown");
}

static void print_pwd(void)
{
    int slash = 0;
    int slash_cpy = 0;
    char *pwd = calloc(1, 100);

    pwd = getcwd(pwd, 100);
    for (int j = 0; pwd[j] != '\0'; j++) {
        if (pwd[j] == '/')
            slash++;
    }
    for (int i = 0; pwd[i] != '\0'; i++) {
        if (pwd[i] == '/')
            slash_cpy++;
        else if (slash_cpy >= slash)
            my_putchar(pwd[i]);
    }
    free(pwd);
}

static void print_display(char **env, shell_t *shell)
{
    my_putchar('/');
    print_log_name(env);
    my_putstr(" | ");
    print_pwd();
    my_putchar('\\');
    dprintf(1, " %i", shell->return_value);
    my_putstr(" $> ");
}

void exec_functions(shell_t *shell)
{
    char *line = NULL;
    char **args = {NULL};
    char **commands = {NULL};
    tree_t *tree = NULL;

    print_display(shell->env_dup, shell);
    line = getnewline(shell);
    line = is_inhibitor(line);
    tree = create_tree_from_input(line);
    shell->sep_list = setup_sep_list(tree);
    list_functions(tree, args, shell);
    free_utility(line, args);
    free_tab(commands);
}
