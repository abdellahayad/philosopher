NAME = philo

CC = cc

FLAG = -Wall -Wextra -Werror 

SRC = initialization.c philo.c parssing.c utils.c create.c\
	monitor.c help.c routine.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAG) $(OBJ) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(FLAG) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) 

re: fclean all