SRC =
OBJ = $(SRC:.c=.o)
CC = cc -Wall -Wextra -Werror
CFLAGS = -g -fsanitize=address
RM = rm -f
NAME = philo

