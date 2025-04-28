NAME = philo

CC = cc

FLAG = -Wall -Wextra -Werror

SRC = initialization.c main.c parssing.c utils.c create.c monitor.c destroy.c

OBJ = $(SRC:.c=.o)

all: $(NAME) clean

$(NAME): $(OBJ)
	$(CC) $(FLAG) $(OBJ) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(FLAG) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all