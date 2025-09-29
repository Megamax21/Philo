# Compiler and flags
CC      := gcc
CFLAGS  := -Wall -Wextra -Werror -g
SRC     := $(wildcard *.c)
OBJ     := $(SRC:.c=.o)
NAME    := philo
HEADER  := philo.h

# Default target
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lpthread

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug: CFLAGS += -DDEBUG_MODE=1 -ggdb
debug: re

.PHONY: all clean fclean re debug