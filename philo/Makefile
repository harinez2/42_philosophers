NAME		= philo
SRCS		= \
				libft.c \
				libutil.c \
				error.c \
				philosopher.c \
				main.c
HEADERS		= main.h
OBJS		= $(SRCS:.c=.o)
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -pthread
DBGFLG		= -g3 -fsanitize=address -fsanitize=leak

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

debug: $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(DBGFLG) $(SRCS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
