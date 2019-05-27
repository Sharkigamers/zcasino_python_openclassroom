/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** op_section
*/

#include "mysh.h"

#ifndef OP_SECTION_
#define OP_SECTION_

static inline int check_history_flag(char *hstr, int db_flag_err, int i)
{
    if (db_flag_err == 1 && (hstr[i] != 'a' && hstr[i] != 'n' && hstr[i] !=
        'r' && hstr[i] != 'w' && hstr[i] != 'c' && hstr[i] != 'p' && hstr[i]
        != 's' && hstr[i] != 'h' && hstr[i] != 'S' && hstr[i] != 'L' &&
        hstr[i] != 'M' && hstr[i] != 'T' && hstr[i] != '-'))
        return (1);
    return (0);
}

static inline int moove_to_next_char(char *name, int *j, char stop)
{
    for (; name[*j] != stop && name[*j] != '\0'; (*j)++);
    if (name[*j] == stop)
        return (0);
    return (1);
}

static inline int moove_to_star(char *str, char *name, int *k, int *j)
{
    for (; str[*k] != '*' && str[*k] != '\0' &&
            str[*k] == name[*j]; (*k)++, (*j)++);
    if (str[*k] == '/')
        return (3);
    if (str[*k] == '*')
        return (0);
    if (str[*k] == '\0' && name[*j] == '\0')
        return (2);
    return (1);
}

char **fill_history_var(char **);
char *find_history(char **);
void fill_var_history(char ***, char *);
int history_flag_c(char **);

#endif
