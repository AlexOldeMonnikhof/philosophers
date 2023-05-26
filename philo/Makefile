NAME = philo
FLAGS = -Wall -Werror -Wextra
SRCS = main.c parse.c checks.c utils.c threads.c routine.c time.c cleanup.c
OBJS	= $(addprefix obj/, ${SRCS:.c=.o})
CC		=	gcc

all: obj/ $(NAME) 

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

obj/%.o: %.c
	$(CC) -c $(FLAGS) -o $@ $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re