/*
** EPITECH PROJECT, 2018
** my_itoa.c
** File description:
** integer to array
*/

#include "mysh.h"

#include <stdlib.h>

char *my_itoa(int number)
{
    int lenght = 0;
    char *buffer;

    if (number == 0) {
        buffer = calloc(sizeof(char), 2);
        buffer[0] = '0';
        return (buffer);
    }
    for (int temp = number; temp > 0; temp = temp / 10)
        lenght++;
    buffer = calloc(1, sizeof(char) * (lenght + 1));
    while (lenght--) {
        buffer[lenght] = number % 10  + '0';
        number = number / 10;
    }
    return (buffer);
}
