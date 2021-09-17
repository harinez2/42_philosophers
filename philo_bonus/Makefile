NAME		= philo_bonus
INCLUDE		= -I./includes
SRC_DIR		= srcs
SRCS		= \
				$(SRC_DIR)/error.c \
				$(SRC_DIR)/lib_ft.c \
				$(SRC_DIR)/philosopher.c \
				$(SRC_DIR)/main.c
OBJS		= $(SRCS:.c=.o)
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -pthread

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) -o $(NAME)

.c.o: $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $(<:.c=.o)

debug: $(SRCS)
	$(CC) $(CFLAGS) $(DBGFLG) $(SRCS) $(INCLUDE) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
