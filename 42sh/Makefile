##
## EPITECH PROJECT, 2019
## minishell1
## File description:
## Makefile
##

SRC	=	$(shell find ./ -name '*.c' ! -name unit_tests.c)	\

OBJ	=	$(SRC:.c=.o)

TEST	=	$(shell find ./ -name '*.c' ! -name main.c)	\

CC	=	gcc -I./include

NAME	=	42sh

C_FLAGS	=	-W -Wall -Werror -Wextra -pedantic

all:	$(NAME)

tests_run:	$(TEST)
	$(CC) -o unit_tests $(TEST) -lcriterion --coverage
	./unit_tests | gcovr

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	rm -f $(shell find $(SOURCEDIR) -name '*.o')
	rm -f $(shell find $(SOURCEDIR) -name '*~')
	rm -f $(shell find $(SOURCEDIR) -name '*#')
	rm -f $(shell find $(SOURCEDIR) -name '*vg*')
	rm -f $(shell find $(SOURCEDIR) -name '*.gc*')


fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all tests_run clean fclean re
