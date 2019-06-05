#!/usr/bin/env python3
##
## EPITECH PROJECT, 2019
## zcasino
## File description:
## tp
##

from random import randrange
from math import ceil

def choose_game(money):
    choice = int(input("Where do you want to place your token (0, 49) ? : "))
    ammount = int(input("How many money do you want to bet ? : "))

    while (choice < 0 or (choice) > 49 or ammount < 0 or ammount > money):
        choice = int(input("Where do you want to place your token (0, 49) ? : "))
        ammount = int(input("How many money do you want to bet ? : "))
    money += gameplay(1, 50, choice, ammount)
    return (money)

def gameplay(min_case, max_case, choice, ammount):
    res = randrange(min_case, max_case)

    if (choice == res):
        print("You earn : ", ammount * 3)
        return (ammount * 3)
    if ((res == 0 or res % 2 == 0) and (choice == 0 or choice % 2 == 0)):
        print("Red : You earn", -ceil(ammount * 0.5))
        return (-ceil(ammount * 0.5))
    if ((res == 1 or res % 3 == 0) and (choice == 1 or choice % 3 == 0)):
        print("Black : You earn", -ceil(ammount * 0.5))
        return (-ceil(ammount * 0.5))
    return (-ammount)

def restart_game(restart, money):
    print("Your current money is about : ", money)
    if (money == 0):
        print("You lost all of your money you can leave the table")
        return (1)
    restart = str(input("Would you want to continue to play ? : "))
    while (restart != "yes" and restart != "no"):
        restart = str(input("Would you want to continue to play ? : "))
    if (restart == "no"):
        return (2)
    return (0)

def zcasino():
    money = 1000
    restart = "yes"
    leave = 0
    choice = 0
    ammount = 0

    print("Your current money is about : ", money)
    while (restart == "yes"):
        money = choose_game(money)        
        leave = int(restart_game(restart, money))
        if (leave == 1):
            return (1)
        elif (leave == 2):
            break
    print("You have : ", money, "$")
    return (0)

def main():
    if (zcasino() == 0):
        print("You left the table")
    else:
        print("You left the casino fustrated")

main()
