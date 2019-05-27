/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** globbing_interrogation_point.
*/

#include "mysh.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

int str_cmp_int(char *str, char *f_name)
{
    int near = 0;

    if (strlen(str) != strlen(f_name))
        return (-1);
    else
        near++;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != '?' && str[i] != f_name[i])
            return (-1);
        if (str[i] == f_name[i])
            near++;
    }
    return (near);
}

char *delete_interrogation_point(DIR *repo, char *str, char *binary)
{
    struct dirent *file;
    int index = 0;
    char *f_name = NULL;
    int near = 0;

    for (int i = 0, cmp = 0; (file = readdir(repo)) != NULL; i++)
        if ((cmp = str_cmp_int(str, file->d_name)) > near) {
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

char *prepare_directory(char *str, char **tab, char *binary)
{
    DIR *repo;
    int index = 2;

    for (int i = 0; tab[i + 1] != NULL; i++) {
        repo = opendir(str);
        if (repo != NULL)
            tab[i + 1] = delete_interrogation_point(repo, tab[i + 1], binary);
        for (int j = 0; tab[i + 1][j] != '\0'; index++, j++)
            str[index] = tab[i + 1][j];
        index++;
    }
    for (int i = 0; tab[i] != NULL; i++)
        free(tab[i]);
    free(tab);
    return (str);
}

char *interrogation_point(char *str, char *binary)
{
    char **tab = {NULL};

    if (str == NULL)
        return (NULL);
    str = my_strcat("./", str);
    tab = str_to_tab(str, '/');
    for (int i = 2; str[i] != '\0'; i++)
        str[i] = '/';
    str = prepare_directory(str, tab, binary);
    for (int i = 0; str[i] != '\0'; i++) {
        if (i <= strlen(str) - 2)
            str[i] = str[i + 2];
        else
            str[i] = '\0';
    }
    return (str);
}

char *check_interrogation_point(char *str, char *binary)
{
    int go = 0;

    if (str == NULL)
        return (NULL);
    for (int i = 0; str[i] != '\0'; i++)
        if (str[0] != '-' && str[i] == '?')
            go++;
    if (go != 0)
        str = interrogation_point(str, binary);
    return (str);
}
