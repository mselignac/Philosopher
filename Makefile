NAME = philo

SRCS = main.c \
		philos.c \
		utils.c \
		time.c \
		init.c

OBJS = ${SRCS:.c=.o}

CFLAGS = -pthread -Wall -Wextra -Werror
#CFLAGS	+=	-g -fsanitize=thread

CC = gcc

all: $(NAME)

bonus: all

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "\033[1;92m\tCompilation Done\033[0m"

clean:
	rm -rf $(OBJS)
	@echo "\033[1;93m\tAll objects deleted\033[0m"

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re bonus
