/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** sample text
*/

#include "mysh.h"

#include <stddef.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void print_unvalid(char *line)
{
    my_putstr_err(line);
    my_putstr_err(": ");
    my_putstr_err("Exec format error. Wrong Architecture.\n");
    exit(1);
}

int is_completed(char *line, char **args, shell_t *shell, tree_t **right)
{
    pid_t child;
    int status = 0;

    if (access(get_bin(line), X_OK) == 0 && opendir(line) == NULL) {
        child = fork();
        if (!child) {
            signal(SIGINT, SIG_DFL);
            if (execve(line, args, shell->env_dup) == -1)
                print_unvalid(line);
        }
        else {
            waitpid(child, &status, WUNTRACED);
            check_status(status, shell);
            return (0);
        }
    }
    return (1);
}
