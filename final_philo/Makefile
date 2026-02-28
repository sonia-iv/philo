CC = cc 

CFLAGS = -Wall -Wextra -Werror -g3

THFLAG = -pthread

NAME = philo

SRC = main.c init.c utils_init.c \
philos_dining.c thread_ph_routine.c \
utils_routine.c utils_time.c philo_finish_dining.c 

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
				$(CC) $(CFLAGS) -o $(NAME) $(THFLAGS) $(OBJS)

%.o: %.c 
		$(CC) $(CFLAGS) -c $< -o $@

clean: 
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all
