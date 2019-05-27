/*
** EPITECH PROJECT, 2018
** my_hex_convertor
** File description:
** hex_convertor with min chars
*/

#include "mysh.h"

#include <stdlib.h>

void my_hex_convertor_min(unsigned int nb)
{
    int i = 0;
    int temp = 0;
    char *hexa = calloc(1, 20);

    while (nb != 0) {
        temp = 0;
        temp = nb % 16;
        if (temp < 10) {
            hexa[i] = temp + 48;
            i++;
        } else {
            hexa[i] = temp + '7';
            i++;
        }
        nb = nb / 16;
    }
    hexa = my_replace(hexa, '0', '\0');
    hexa = my_revstr(hexa);
    my_putstr(hexa);
}
