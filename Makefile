CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS = stack.c push_swap.c
OBJS = $(SRCS:.c=.o)
NAME = push_swap

all: $(NAME)

$(NAME): $(OBJS)
    $(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
    rm -f $(OBJS)

fclean: clean
    rm -f $(NAME)

re: fclean all