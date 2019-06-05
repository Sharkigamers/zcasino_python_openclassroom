/*
** EPITECH PROJECT, 2019
** more_or_less
** File description:
** main
*/

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

int replay(void)
{
    char *buf = NULL;
    size_t len = 0;

    printf("Would you want to continue to play ? : ");
    if (getline(&buf, &len, stdin) == -1) {
        return (1);
    }
    while (strcmp(buf, "yes\n") != 0 && strcmp(buf, "no\n") != 0) {
        free(buf);
        len = 0;
        printf("Would you want to continue to play ? : ");
        if (getline(&buf, &len, stdin) == -1)
            return (1);
    }
    if (strcmp(buf, "no\n") == 0) {
        free(buf);
        return (2);
    }
    free(buf);
    return (0);
}

int choose_dif(void)
{
    int diff = 0;
    char *buf = NULL;
    size_t len = 0;

    printf("Choose you difficulty between 1 and 3 : ");
    if (getline(&buf, &len, stdin) == -1)
        return (-1);
    while (atoi(buf) < 1 || atoi(buf) > 3) {
        free(buf);
        len = 0;
        printf("Choose you difficulty between 1 and 3 : ");
        if (getline(&buf, &len, stdin) == -1)
            return (-1);
    }
    buf[strlen(buf) - 1] = '\0';
    diff = atoi(buf);
    free(buf);
    return (pow(100, diff));
}

int gameplay(int win, int number, size_t len)
{
    char *buf = NULL;

    while (win != 1) {
        printf("What is your number ? : ");
        if (getline(&buf, &len, stdin) == -1)
            return (1);
        buf[strlen(buf) - 1] = '\0';
        if (atoi(buf) < number)
            printf("More !!!\n");
        else if (atoi(buf) > number)
            printf("Less !!!\n");
        else {
            printf("You found it !!\n");
            win = 1;
        }
        free(buf);
        buf = NULL;
    }
    return (0);
}

int more_less(void)
{
    int play = 0;
    int win = 0;
    char *buf = NULL;
    size_t len = 0;
    int number = 0;

    srand(time(NULL));
    while (play == 0) {
        number = choose_dif();
        if (number == -1)
            return (1);
        number = rand() % number + 1;
        len = 0;
        if (gameplay(win, number, len) == 1)
            return (1);
        play = replay();
    }
    return (play);
}

int main(int ac, char **av)
{
    int return_val = 0;

    if (ac != 1)
        return (84);
    return_val = more_less();
    if (return_val == 2)
        return (0);
    else
        return (return_val);
}
