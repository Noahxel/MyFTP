##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## compile main.c and u.t
##

SRCTEST		=		test/test_project.c

SRC			=	src/close_n_die.c			\
				src/server.c				\
				src/main.c					\
				src/clients_requests.c		\
				src/put_messages.c			\
				src/my_str_to_word_array.c	\
				src/my_strcat.c				\
				src/auth.c					\
				src/directory.c				\
				src/pasv.c					\
				src/port.c					\
				src/misc_fctns.c			\
				src/help.c					\
				src/dele.c

TEST		=	unit_tests

NAME		=	myftp

OBJ			=	$(SRC:.c=.o)

CFLAGS		=		-Wall -Wextra
TFLAGS		=		--coverage -lcriterion

all:	$(OBJ)
		gcc $(CFLAGS) $(OBJ) -o $(NAME)

tests_run:
		gcc $(CFLAGS) $(SRCTEST) $(SRC) -o $(TEST) $(TFLAGS)
		./unit_tests
clean:
		rm -f *.o
		rm -f src/*.o

fclean: clean
		rm -f *.gcno
		rm -f *.gcda
		rm -f $(TEST)
		rm -f $(NAME)

re: fclean all
