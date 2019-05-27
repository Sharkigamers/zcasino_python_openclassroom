/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** handle cd built-in
*/

#include "mysh.h"

#include <stddef.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

static void move(shell_t *shell, char **args)
{
    int r_value = chdir(args[1]);
    struct stat sb;

    if (r_value == -1) {
        if (lstat(args[1], &sb) != -1 && sb.st_mode != S_IFDIR) {
            my_putstr_err(args[1]);
            my_putstr_err(": Not a directory.\n");
            shell->return_value = 1;
        } else {
            my_putstr_err(args[1]);
            my_putstr_err(": No such file or directory.\n");
            shell->return_value = 1;
        }
    } else
        shell->return_value = 0;
}

static int check_cd_error(shell_t *shell, char **args)
{
    if (args[2] != NULL) {
        my_putstr_err("cd: Too many arguments.\n");
        shell->return_value = 1;
        return 1;
    }
    return 0;
}

static int handle_dash(shell_t *shell, char **args)
{
    char *oldpwd = find_old_pwd(shell);
    char *actual = get_pwd();

    if (oldpwd == NULL) {
        move(shell, args);
        return 1;
    }
    else if (oldpwd != NULL)
        args[1] = oldpwd;
    move(shell, args);
    update_shell(shell, actual);
    return 1;
}

int my_cd(shell_t *shell, char **args)
{
    char *actual = get_pwd();

    if (!my_strcmp(args[1], "-") && handle_dash(shell, args))
        return (0);
    !my_strcmp(args[1], "~") || !my_strcmp(args[1], "--")
        ? args[1] = NULL : args[1];
    if (args[1] == NULL) {
        shell->return_value = 0;
        chdir(shell->home);
    }
    else if (check_cd_error(shell, args));
    else
        move(shell, args);
    update_shell(shell, actual);
    return (0);
}
