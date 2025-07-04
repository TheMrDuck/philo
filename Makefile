SRC = main.c philos_routine.c utils.c timer.c
OBJ = $(SRC:.c=.o)
CC = cc -Wall -Wextra -Werror
CFLAGS = -g  -pthread
RM = rm -f
NAME = philo

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -I. $(OBJ) -o philo

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
