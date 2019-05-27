/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** history
*/

#include <time.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "mysh.h"

void fill_var_history(char ***history, char *input)
{
    size_t sec_time = time(NULL);
    char *str_time = my_itoa(sec_time);
    int i = 0;
    int k = 2;

    for (; (*history)[i] != NULL; i++);
    *history = realloc(*history, sizeof(char *) * (i + 3));
    *history == NULL ? exit(84) : 0;
    (*history)[i] = malloc(sizeof(char *) * strlen(str_time) + 4);
    if ((*history)[i] == NULL)
        exit(84);
    (*history)[i][0] = '#';
    (*history)[i][1] = '+';
    for (int j = 0; str_time[j] != '\0'; j++, k++)
        (*history)[i][k] = str_time[j];
    (*history)[i][k] = '\n';
    (*history)[i][k + 1] = '\0';
    (*history)[i + 1] = strdup(input);
    (*history)[i + 2] = NULL;
    free(str_time);
}

static char **fill_in(char **history, char *path)
{
    FILE *fd = fopen(path, "r");
    char *buff = NULL;
    size_t len = 0;
    int i = 0;

    for (; getline(&buff, &len, fd) > 0; i++) {
        history[i] = strdup(buff);
        free(buff);
        buff = NULL;
        len = 0;
    }
    history[i] = NULL;
    fclose(fd);
    free(buff);
    free(path);
    return (history);
}

static int check_exisitng_file(FILE *fd, char ***history)
{
    int i = 0;
    char *buff = NULL;
    size_t len = 0;

    if (fd == NULL) {
        *history = malloc(sizeof(char *) * 1);
        if (*history == NULL)
            return (-84);
        (*history)[0] = NULL;
        return (-1);
    }
    for (; getline(&buff, &len, fd) > 0; i++) {
        free(buff);
        buff = NULL;
        len = 0;
    }
    free(buff);
    return (i);
}

char **fill_history_var(char **save_env)
{
    char *path = find_history(save_env);
    FILE *fd = NULL;
    char **history = NULL;
    char *buff = NULL;
    size_t len = 0;
    int i;

    if (path != NULL)
        fd = fopen(path, "r");
    i = check_exisitng_file(fd, &history);
    if (i == -84)
        exit(84);
    if (i == -1)
        return (history);
    history = malloc(sizeof(char *) * (i + 1));
    if (history == NULL)
        return (NULL);
    fclose(fd);
    fill_in(history, path);
    return (history);
}

char *find_history(char **save_env)
{
    char *save = ".my42sh_history";
    char *var_env = NULL;
    char *semi_res = NULL;
    char *final_res = NULL;;

    for (int i = 0; save_env[i] != NULL; i++) {
        if (!my_strcmpn(save_env[i], "HOME=", 5)) {
            var_env = strdup(save_env[i]);
            semi_res = my_strncat(var_env, "/", strlen("HOME="));
            final_res = my_strcat(semi_res, save);
            free(semi_res);
            free(var_env);
            return (final_res);
        }
    }
    return (NULL);
}
