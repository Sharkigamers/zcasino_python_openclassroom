/*
** EPITECH PROJECT, 2018
** my_lib
** File description:
** my replace
*/

#include "mysh.h"

char *my_replace(char *str, char target, char replace)
{
    for (int i = 0; str[i] != '\0'; i++)
        str[i] == target ? str[i] = replace : str[i];
    return (str);
}
