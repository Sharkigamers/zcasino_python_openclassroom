/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** dups
*/

#include <unistd.h>

#include "mysh.h"
#include "tree.h"

void handle_dups(fd_t *fds, tree_t **right)
{
    if ((fds->count / 2) == fds->nb_pipes)
        dup2(1, 1);
    else
        dup2(fds->pipefd[fds->count + 1], 1);
    if (fds->count != 0)
        dup2(fds->pipefd[fds->count - 2], 0);
    if (fds->count == 0 && right != NULL &&
        right[0] != NULL && right[0]->redir_type >= 3) {
        redirect_by_index(fds->pipefd[0], right[0]->line, right[0]->redir_type);
        dup2(fds->pipefd[0], 0);
    }
    if (fds->count == 0 && right != NULL &&
        right[1] != NULL && right[1]->redir_type >= 3) {
        redirect_by_index(fds->pipefd[0], right[1]->line, right[1]->redir_type);
        dup2(fds->pipefd[0], 0);
    }
}
