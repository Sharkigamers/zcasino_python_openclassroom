/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** fill_file_history
*/

#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "mysh.h"

void fill_history_file(char **history, char **save_env, shell_t *shell)
{
    char *path = find_history(save_env);
    int fd;

    if (path == NULL)
        path = ".";
    fd = open(path, O_WRONLY | O_TRUNC, 0664);
    if (fd == -1) {
        fd = open(path, O_CREAT | O_WRONLY, 0664);
    }
    for (int i = shell->history_pointer; history[i] != NULL; i++)
        write(fd, history[i], strlen(history[i]));
    if (fd != -1)
        close(fd);
}
