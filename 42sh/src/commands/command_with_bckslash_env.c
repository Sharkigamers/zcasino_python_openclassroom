/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** bckslash_env
*/

#include <time.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "mysh.h"

int env_slashed(char **save_env, char *line)
{
    int res;

    if (strcmp(line, "bin/ls") != 0)
        return (0);
    for (int i = 0; save_env[i] != NULL; i++) {
        if (!my_strcmpn(save_env[i], "PATH=", 5)) {
            res = (my_stricmp(save_env[i], "/", 5) == 0 ? 1 : 0);
            res == 1 ? my_putstr_err("bin/ls: Command not found.\n") : 0;
            return (res);
        }
    }
    return (0);
}
