/*
** EPITECH PROJECT, 2019
** my_delete_char.c
** File description:
** my_delete_char.
*/

#include <stdlib.h>

void delete_char(char *str, char chara)
{
    char *new_str;
    char *str_cpy;

    for (new_str = str_cpy = str; *new_str != '\0'; new_str++) {
        *str_cpy = *new_str;
        if (*str_cpy != chara)
            str_cpy++;
    }
    *str_cpy = '\0';
}
