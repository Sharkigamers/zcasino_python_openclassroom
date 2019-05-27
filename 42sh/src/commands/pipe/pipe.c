/*
** EPITECH PROJECT, 2019
** pipe.c
** File description:
** pipes.
*/

#include "mysh.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

void handle_pipe(char **cmd, shell_t *shell, tree_t **right, fd_t *fds)
{
    handle_dups(fds, right);
    for (int i = 0; i != fds->nb_pipes * 2; i++)
        close(fds->pipefd[i]);
    if (right != NULL && right[0]->redir_type == 1 &&
        (fds->count / 2) == fds->nb_pipes ||
        right != NULL && right[0]->redir_type == 2 &&
        (fds->count / 2) == fds->nb_pipes)
        seek_command(cmd[0], cmd, shell, right);
    else
        seek_command(cmd[0], cmd, shell, NULL);
    exit(shell->return_value);
}

static fd_t *get_fds(int pipefd[], int pipes)
{
    fd_t *fd = malloc(sizeof(fd_t));

    if (fd == NULL)
        exit(84);
    fd->pipefd = pipefd;
    fd->nb_pipes = pipes;
    fd->count = 0;
    return (fd);
}

static int handle_pipe_loop(char ***cmd, int pipes, shell_t *shell,
                            tree_t **right)
{
    int pipefd[pipes * 2];
    fd_t *fds = NULL;
    pid_t father;

    for (int i = 0; i != pipes; i++)
        pipe(pipefd + (2 * i));
    fds = get_fds(pipefd, pipes);
    for (int i = 0; i <= pipes; i++, fds->count += 2) {
        father = fork();
        if (!father)
            handle_pipe(cmd[i], shell, right, fds);
    } for (int i = 0; i != pipes * 2; i++)
        close(pipefd[i]);
    for (int i = 0; i <= pipes; i++)
        wait(NULL);
}

static int check_pipe(char *line)
{
    int check = 0;

    for (int i = 0; line[i] != '\0'; i++)
        check += (line[i] == '|' ? 1 : 0);
    return (check);
}

int is_a_pipe(char *line, shell_t *shell, tree_t **right)
{
    int is_pipe = check_pipe(line);
    char **commands = {NULL};
    char ***arguments = {NULL};

    if (!is_pipe)
        return (1);
    commands = setup_commands(line);
    arguments = get_arguments(commands);
    handle_pipe_loop(arguments, is_pipe, shell, right);
    return (0);
}
