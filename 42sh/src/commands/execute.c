/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** execute functions
*/

#include "mysh.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int get_semis(char *line)
{
    int semis = 0;

    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == ';')
            semis++;
    }
    return (semis);
}

int redirect(char *string, char **args, shell_t *shell, tree_t *right)
{
    pid_t child;
    int status = 0;
    int pipefd[2];

    pipe(pipefd);
    child = fork();
    if (!child) {
        close(pipefd[0]);
        dup2(pipefd[1], 1);
        signal(SIGINT, SIG_DFL);
        execve(string, args, shell->env_dup);
    }
    else {
        close(pipefd[1]);
        redirect_by_index(pipefd[0], right->line, right->redir_type);
        close(pipefd[0]);
        waitpid(child, &status, WUNTRACED);
        check_status(status, shell);
    }
    return (1);
}

int input(char *string, char **args, shell_t *shell, tree_t *right)
{
    pid_t child;
    int status = 0;
    int pipefd[2];

    pipe(pipefd);
    child = fork();
    if (!child) {
        close(pipefd[1]);
        dup2(pipefd[0], 0);
        signal(SIGINT, SIG_DFL);
        close(pipefd[1]);
        execve(string, args, shell->env_dup);
    } else {
        close(pipefd[0]);
        redirect_by_index(pipefd[1], right->line, right->redir_type);
        close(pipefd[1]);
        waitpid(child, &status, WUNTRACED);
        check_status(status, shell);
    }
    return (1);
}

static int is_redirect(tree_t **right, char *string, char **args,
                        shell_t *shell)
{
    if (right == NULL)
        return (0);
    if (right != NULL && right[0]->redir_type == 1 ||
        right != NULL && right[0]->redir_type == 2 )
        return (redirect(string, args, shell, right[0]));
    else if (right != NULL && right[0]->redir_type == 3 ||
            right != NULL && right[0]->redir_type == 4 )
        return (input(string, args, shell, right[0]));
    if (right != NULL && right[1]->redir_type == 1 ||
        right != NULL && right[1]->redir_type == 2 )
        return (redirect(string, args, shell, right[1]));
    else if (right != NULL && right[1]->redir_type == 3 ||
            right != NULL && right[1]->redir_type == 4 )
        return (input(string, args, shell, right[1]));
    return (0);
}

int execute_command(char *string, char **args, shell_t *shell, tree_t **right)
{
    pid_t child;
    int status = 0;

    if (is_redirect(right, string, args, shell))
        return (0);
    child = fork();
    if (!child) {
        signal(SIGINT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);
        execve(string, args, shell->env_dup);
    }
    else {
        waitpid(child, &status, WUNTRACED);
        check_status(status, shell);
        free(string);
    }
    return (0);
}
