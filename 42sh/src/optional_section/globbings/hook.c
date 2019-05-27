/*
** EPITECH PROJECT, 2019
** 42sh.
** File description:
** hook_command.
*/

#include "mysh.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

int str_cmp_int_hook(char *str, char *f_name)
{
    int near = 0;
    int  hook = 0;

    for (int i = 0, y = 0; str[i] != '\0'; i++, y++) {
        if (hook % 2 == 0 && str[i] == '[')
            hook++;
        if (hook % 2 != 0 && str[i] == ']')
            hook++;
        if (hook % 2 == 0 && str[i] != ']' && str[i] != f_name[y])
            return (-1);
        if (str[i] == f_name[y])
            near++;
        if (hook % 2 != 0)
            y--;
    }
    return (near);
}

char *delete_hook(DIR *repo, char *str, char *binary)
{
    struct dirent *file;
    int index = 0;
    char *f_name = NULL;
    int near = 0;

    for (int i = 0, cmp = 0; (file = readdir(repo)) != NULL; i++)
        if ((cmp = str_cmp_int_hook(str, file->d_name)) > near) {
            near = cmp;
            index = i;
        }
    if (near <= 0)
        return (error(str, binary));
    rewinddir(repo);
    for (int i = 0; (file = readdir(repo)) != NULL; i++)
        if (i == index) {
            f_name = strdup(file->d_name);
            closedir(repo);
            return (f_name);
        }
}

char *prepare_directory_hook(char *str, char **tab, char *binary)
{
    DIR *repo;
    int index = 2;

    for (int i = 0; tab[i + 1] != NULL; i++) {
        repo = opendir(str);
        if (repo != NULL)
            tab[i + 1] = delete_hook(repo, tab[i + 1], binary);
        for (int j = 0; tab[i + 1][j] != '\0'; index++, j++)
            str[index] = tab[i + 1][j];
        index++;
    }
    for (int i = 0; tab[i] != NULL; i++)
        free(tab[i]);
    free(tab);
    return (str);
}

char *hook(char *str, char *binary)
{
    char **tab = {NULL};

    if (str == NULL)
        return (NULL);
    str = my_strcat("./", str);
    tab = str_to_tab(str, '/');
    for (int i = 2; str[i] != '\0'; i++)
        str[i] = '/';
    str = prepare_directory_hook(str, tab, binary);
    for (int i = 0; str[i] != '\0'; i++) {
        if (i <= strlen(str) - 2)
            str[i] = str[i + 2];
        else
            str[i] = '\0';
    }
    return (str);
}

char *check_hook(char *str, char *binary)
{
    int go = 0;

    if (str == NULL)
        return (NULL);
    for (int i = 0; str[i] != '\0'; i++) {
        if (go % 2 == 0 && str[0] != '-' && str[i] == '[' ||
            go % 2 != 0 && str[0] != '-' && str[i] == ']')
            go++;
        else if (go % 2 != 0 && str[0] != '-' && str[i] == '[' ||
                go % 2 == 0 && str[0] != '-' && str[i] == ']') {
            return (error(str, binary));
        }
    }
    if (go % 2 == 0 && go != 0)
        str = hook(str, binary);
    return (str);
}
