/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** write error message.
*/

#include "mysh.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *error(char *str, char *binary)
{
    my_printf("%s", binary);
    my_putstr_err(" No match.\n");
    return (str);
}
