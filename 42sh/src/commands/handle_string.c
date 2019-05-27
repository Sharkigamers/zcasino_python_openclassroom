/*
** EPITECH PROJECT, 2019
** minishell1
** File description:
** malloc and stuff
*/

#include "mysh.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <dirent.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

int is_a_wave(char *line, char **args, shell_t *shell)
{
    pid_t child;
    int status = 0;

    if (my_strcmpn(line, "~", 1) == 0 && access(update_wave(line, shell), X_OK)
        == 0 && opendir(update_wave(line, shell)) == NULL) {
        child = fork();
        if (!child)
            execve(update_wave(line, shell), args, shell->env_dup);
        else {
            waitpid(child, &status, WUNTRACED);
            check_status(status, shell);
            return (0);
        }
    }
    return (1);
}

void check_status(int status, shell_t *shell)
{
    if (!WIFEXITED(status)) {
        shell->return_value = WTERMSIG(status) + 128;
        WTERMSIG(status) != 8 ? my_putstr_err(strsignal(WTERMSIG(status))) : 0;
        WTERMSIG(status) == 8 ? my_putstr_err("Floating exception") : 0;
        WCOREDUMP(status) == 128 ? my_putstr_err(" (core dumped)") : 0;
        my_putchar('\n');
    } else
        shell->return_value = WEXITSTATUS(status);
}

char *get_home(char **env)
{
    int path_index = get_indexes(env);
    int i = 0;
    int count = 0;
    char *home;
    int check = 0;

    for (; i != path_index; i++) {
        if (my_strcmpn(env[i], "HOME", 4) == 0) {
            check = 1;
            break;
        }
    }
    if (check == 0)
        return (NULL);
    home = my_calloc(sizeof(char) * my_strlen(env[i]));
    if (home == NULL)
        exit(84);
    for (int j = 5; j != my_strlen(env[i]); j++, count++)
        home[count] = env[i][j];
    return (home);
}

void print_error(char *line, shell_t *shell)
{
    if (shell->dir_error == 1) {
        my_putstr_err(line);
        my_putstr_err(": Permission denied.\n");
        shell->return_value = 1;
        shell->dir_error = 0;
    } else if (shell->errno_value == ENOEXEC) {
        my_putstr_err(line);
        my_putstr_err(": cannot execute binary file\n");
        shell->return_value = 84;
    } else{
        my_putstr_err(line);
        my_putstr_err(": Command not found.\n");
        shell->return_value = 1;
    }
}

int is_valid_input(char *line, shell_t *shell, char **args, tree_t **right)
{
    char *string = calloc(1, sizeof(char) * (strlen(line) + 1));
    DIR *dir = NULL;

    if (shell->path == NULL)
        shell->path = path_replacement();
    for (int i = 0; shell->path[i] != NULL; i++) {
        string = my_strcat(shell->path[i], line);
        dir = opendir(line);
        if (access(string, X_OK) == 0
            && dir == NULL) {
            execute_command(string, args, shell, right);
            return (0);
        }
        if (dir != NULL)
            closedir(dir);
        free(string);
    }
    return (1);
}
