/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** check_error_history
*/

#include <unistd.h>
#include <stddef.h>

#include "mysh.h"
#include "op_section.h"

static int gest_more_error(char *hstr, int db_flag_err, int i)
{
    int dash = 0;

    if (hstr[i] >= '0' && hstr[i] <= '9' && db_flag_err == 0) {
        for (int i = 0; hstr[i] != '\0'; i++)
            hstr[i] == '-' ? dash++ : 0;
        if (dash > 0) {
            my_putstr_err("history: Badly formed number.\n");
            return (1);
        }
    }
    if (db_flag_err == 0 && (hstr[i] < '0' || hstr[i] > '9')) {
        my_putstr_err("history: Badly formed number.\n");
        return (1);
    }
    if (check_history_flag(hstr, db_flag_err, i)) {
        my_putstr_err("Usage: history [-chrSLMT] [# number of events].\n");
        return (1);
    }
    return (0);
}

static int gest_bad_param(char *hstr, shell_t *shell)
{
    int db_flag_err = 0;
    int nb_flag_err = 0;

    for (int i = 0; hstr[i] != '\0'; i++) {
        hstr[i] == '-' ? db_flag_err++ : 0;
        if (db_flag_err >= 2) {
            my_putstr_err("history: Too many arguments.\n");
            shell->return_value = 1;
            return (1);
        }
        if (gest_more_error(hstr, db_flag_err, i) == 1) {
            shell->return_value = 1;
            return (1);
        }
    }
    return (0);
}

int check_flags(char **hargs, shell_t *shell)
{
    for (int i = 1; hargs[i] != NULL; i++) {
        if (gest_bad_param(hargs[i], shell) == 1)
            return (1);
    }
    return (0);
}
