/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** handle redirections / pipes
*/

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#include "mysh.h"

int simple_redirection(int pipefd, char *file_name)
{
    int file_fd = 0;
    char buf;

    file_fd = open(file_name,  O_WRONLY | O_TRUNC | O_CREAT, 0666);
    while (read(pipefd, &buf, 1) > 0)
        write(file_fd, &buf, 1);
    return (0);
}

int double_redirection(int pipefd, char *file_name)
{
    int file_fd = open(file_name, O_WRONLY | O_APPEND);
    char buf;

    if (file_fd == -1)
        file_fd = open(file_name,  O_WRONLY | O_APPEND | O_CREAT, 0666);
    while (read(pipefd, &buf, 1) > 0)
        write(file_fd, &buf, 1);
    return (0);
}

int simple_input(int pipefd, char *file_name)
{
    int file_fd = 0;
    char buf;

    file_fd = open(file_name, O_RDONLY);
    while (read(file_fd, &buf, 1) > 0)
        write(pipefd, &buf, 1);
    return (0);
}

int double_input(int pipefd, char *file_name)
{
    char *buf = NULL;
    char *total = calloc(1, 1);
    size_t len = 0;
    ssize_t length = 0;

    while (1) {
        write(1, "? ", 2);
        length = getline(&buf, &len, stdin);
        if (length == -1 || !strcmp(my_strcat(file_name, "\n"), buf))
            break;
        total = my_strcat(total, buf);
    }
    write(pipefd, total, strlen(total));
    return (0);
}

int redirect_by_index(int pipefd, char *file_name, int index)
{
    if (index == 1)
        return (simple_redirection(pipefd, file_name));
    if (index == 2)
        return (double_redirection(pipefd, file_name));
    if (index == 3)
        return (simple_input(pipefd, file_name));
    if (index == 4)
        return (double_input(pipefd, file_name));
    return (0);
}
