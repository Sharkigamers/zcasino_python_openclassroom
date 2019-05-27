/*
** EPITECH PROJECT, 2019
** minishell1
** File description:
** get infos
*/

#include "mysh.h"
#include <stddef.h>

static int is_non_alphanum(char letter)
{
    if (letter < '0')
        return (1);
    if (letter < 'A' && letter > '9')
        return (1);
    if (letter > 'Z' && letter < 'a')
        return (1);
    if (letter > 'z')
        return (1);
    return (0);
}

void update_shell(shell_t *shell, char *actual)
{
    int index = 0;
    char *pwd = get_pwd();

    update_env_by_str(shell, "OLDPWD", actual);
    update_env_by_str(shell, "PWD", pwd);
}

int setenv_err(void)
{
    my_putstr_err("setenv: Variable name must contain"
                    " alphanumeric characters.\n");
    return (1);
}

int check_strings(char **strings)
{
    for (int j = 0; strings[1][j] != '\0'; j++) {
        if (is_non_alphanum(strings[1][j]))
            return (0);
    }
    return (1);
}

int get_exit_value(char *value, shell_t *shell)
{
    int exit_value = 0;

    if (value == NULL) {
        exit_value = shell->return_value % 256;
        return (exit_value);
    }
    else
        exit_value = my_getnbr(value);
    if (exit_value >= 0)
        exit_value = exit_value % 256;
    else
        exit_value = 256 -((exit_value * -1) - 256);
    return (exit_value);
}
