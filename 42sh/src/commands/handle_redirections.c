/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** handle reirections
*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>

#include "mysh.h"

static int throw_in_file(int pipefd, char *file_name)
{
    int file_fd = 0;
    char buf;

    file_fd = open(file_name,  O_WRONLY | O_TRUNC | O_CREAT,
                    S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
    while (read(pipefd, &buf, 1) > 0)
        write(file_fd, &buf, 1);
    return (0);
}

static int get_from_file(int pipefd, char *file_name)
{
    int file_fd = 0;
    char buf;

    file_fd = open(file_name, O_RDONLY);
    while (read(file_fd, &buf, 1) > 0)
        write(pipefd, &buf, 1);
    return (0);
}

void init_redir(char **strings, char ***args, int *pipefd)
{
    *args = get_args(strings[0]);
    strings[0] = my_strcat("/bin/", get_bin(strings[0]));
    pipe(pipefd);
}

int handle_redirections(char **strings, shell_t *shell)
{
    char ***args = malloc(sizeof(char **) * 2);
    pid_t child;
    int status = 0;
    int pipefd[2];

    init_redir(strings, &args[0], pipefd);
    child = fork();
    if (!child) {
        close(pipefd[0]);
        dup2(pipefd[1], 1);
        execve(strings[0], args[0], shell->env_dup);
        close(pipefd[1]);
    }
    else {
        close(pipefd[1]);
        throw_in_file(pipefd[0], strings[1]);
        close(pipefd[0]);
    }
    return (1);
}

int handle_input(char **strings, shell_t *shell)
{
    char ***args = malloc(sizeof(char **) * 2);
    pid_t child;
    int status = 0;
    int pipefd[2];

    init_redir(strings, &args[0], pipefd);
    child = fork();
    if (!child) {
        close(pipefd[1]);
        dup2(pipefd[0], 0);
        execve(strings[0], args[0], shell->env_dup);
    }
    else {
        close(pipefd[0]);
        get_from_file(pipefd[1], strings[1]);
        close(pipefd[1]);
        waitpid(child, &status, WUNTRACED);
    }
    return (1);
}
