/*
** EPITECH PROJECT, 2019
** minishell1
** File description:
** main loop
*/

#include "mysh.h"
#include <stdio.h>
#include <signal.h>

int main(int argc, char **argv, char **env)
{
    shell_t *shell;
    (void) argv;

    if (argc != 1)
        return (84);
    shell = get_struct(env);
    if (shell == NULL)
        return (84);
    shell->history = fill_history_var(shell->env_dup);
    shell->history_pointer = 0;
    signal(SIGINT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    remove_oldpwd(shell);
    while (1)
        exec_functions(shell);
    signal(SIGINT, SIG_DFL);
    return (0);
}
