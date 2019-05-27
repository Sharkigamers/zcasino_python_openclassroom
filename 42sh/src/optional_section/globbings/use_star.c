/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** use_star
*/

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <sys/types.h>
#include <dirent.h>

#include "mysh.h"

void compare_str_star(char *str, char **return_str, char *path)
{
    DIR *dir = opendir(path);
    struct dirent *rent;

    if (strcmp(path, "./") == 0)
        path = "";
    for (int i = 0; (rent = readdir(dir)) != NULL; i++) {
        if (rent->d_name[0] != '.') {
            find_complete_str(rent, str, return_str, path);
        }
        if (str[0] == '.')
            find_complete_str(rent, str, return_str, path);
    }
    closedir(dir);
}

int detect_star(char *str)
{
    int quote = 0;
    int dbquote = 0;
    int bckslash = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        quote = (quote == 2 ? 0 : quote);
        dbquote = (dbquote == 2 ? 0 : dbquote);
        quote += (str[i] == '\'' ? 1 : 0);
        dbquote += (str[i] == '"' ? 1 : 0);
        bckslash += (str[i] == '\\' ? 1 : 0);
        if (str[i] == '*' && quote == 0 && dbquote == 0 && bckslash == 0)
            return (1);
        bckslash = (i != 0 && str[i - 1] == '\\' ? 0 : bckslash);
    }
    return (0);
}

int cond_in_loop(char **args, char **commands, char *save_str, int j)
{
    char *save_cmd = NULL;

    if (detect_star(args[j]) == 1) {
        check_last_char(args[j]);
        save_cmd = strdup(*commands);
        compare_str_star(args[j], commands, "./");
        if (strcmp(*commands, save_cmd) == 0) {
            my_putstr_err(args[0]);
            my_putstr_err(": No match.\n");
            free(save_cmd);
            return (2);
        }
        free(save_cmd);
    } else {
        save_str = my_strcat_with_space(*commands, args[j]);
        free(*commands);
        *commands = strdup(save_str);
        free(save_str);
    }
    return (1);
}

int check_stars(char **args, shell_t *shell)
{
    int flag = 0;

    for (int i = 0; args[i] != NULL; i++) {
        detect_star(args[i]) == 1 ? flag = 1 : 0;
        if (i == 0 && flag == 1) {
            my_putstr_err(args[0]);
            my_putstr_err(": No match.\n");
            shell->return_value = 1;
            return (-2);
        }
    }
    return (flag);
}

int fill_new_string(char **args, char **commands, shell_t *shell)
{
    int flag = 0;
    char *save_str = NULL;

    flag = check_stars(args, shell);
    if (flag == -2)
        return (2);
    if (flag == 0)
        return (0);
    free(*commands);
    *commands = strdup(args[0]);
    for (int j = 1; args[j] != NULL; j++) {
        if (cond_in_loop(args, commands, save_str, j) == 2) {
            shell->return_value = 1;
            return (2);
        }
    }
    return (1);
}
