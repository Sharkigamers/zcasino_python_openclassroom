/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** annex_using_star
*/

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <sys/types.h>
#include <dirent.h>

#include "mysh.h"

char *change_dir(int j, char *name, char *path)
{
    char *new_path = malloc(sizeof(char) * (strlen(path) + j + 2));
    int l;

    if (new_path == NULL)
        exit(84);
    for (l = 0; path[l] != '\0'; l++)
        new_path[l] = path[l];
    for (int k = 0, i = 0; i < j; i++, k++, l++) {
        new_path[l] = name[k];
    }
    new_path[l] = '/';
    new_path[l + 1] = '\0';
    return (new_path);
}

int move_result(int res, char **return_str, struct dirent *rent, char *path)
{
    char *save_str = NULL;

    if (res == 2) {
        save_str = my_strcat(path, rent->d_name);
        *return_str = my_strcat_with_space(*return_str, save_str);
        free(save_str);
    }
    if (res == 1 || res == 2)
        return (1);
    return (0);
}

void find_complete_str(struct dirent *rent, char *str,
                        char **return_str, char *path)
{
    char *new_path = NULL;
    int k = 0;

    for (int i = 0; path[i] != '\0'; i++, k++);
    for (int j = 0, valid_var = 0, res = 0; valid_var == 0 ;) {
        res = moove_to_star(str, rent->d_name, &k, &j);
        valid_var = move_result(res, return_str, rent, path);
        if (res == 3 && rent->d_name[j] == '\0') {
            new_path = change_dir(j, rent->d_name, path);
            compare_str_star(str, return_str, new_path);
            break;
        }
        if (res == 3)
            break;
        for (; str[k + 1] == '*'; k++);
        if (moove_to_next_char(rent->d_name, &j, str[k + 1]) == 1)
            valid_var = 1;
        k++;
    }
}

void check_last_char(char *str)
{
    int i = 0;
    int j;

    for (; str[i] != '\0'; i++);
    for (j = i - 1; i > 0; j--)
        if (str[j] != '/')
            break;
    if (str[j] != '\0')
        str[j + 1] = '\0';
}
