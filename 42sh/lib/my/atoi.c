/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** convert char * to int
*/

#include <stddef.h>

int my_natoi(char const *str, int i)
{
    int nb = 0;
    int neg = 0;

    if (str == NULL)
        return (0);
    for (; str[i] != '\0'; i++) {
        if (str[i] == '-') {
            neg = 1;
            continue;
        }
        nb = (nb * 10) + (str[i] - '0');
    }
    return (neg == 1 ? -nb : nb);
}
