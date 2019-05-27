/*
** EPITECH PROJECT, 2018
** my_hex_convertor
** File description:
** my_hex_convertor
*/

#include "mysh.h"

#include <stdlib.h>

void my_hex_convertor(unsigned int nb)
{
    int i = 0;
    int temp;
    char *hexa = calloc(1, sizeof(char) * 20);

    while (nb != 0) {
        temp = 0;
        temp = nb % 16;
        if (temp < 10) {
            hexa[i] = temp + '0';
        } else
            hexa[i] = temp + 87;
        i++;
        nb = nb / 16;
    }
    hexa = my_replace(hexa, '0', '\0');
    hexa = my_revstr(hexa);
    my_putstr(hexa);
}
