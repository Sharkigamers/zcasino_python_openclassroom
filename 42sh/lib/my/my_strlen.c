/*
** EPITECH PROJECT, 2018
** my_strlen.c
** File description:
** get the lenght of a string
*/

#include "mysh.h"

int my_strlen(char const *str)
{
    int i = 0;

    while (str[i] != '\0')
        i++;
    return (i);
}
