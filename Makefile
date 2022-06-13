NAME = philo

SRCS = philo.c helpers.c

FLAGS = -Wall -Werror -Wextra

OBJ := $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	cc -g -pthread -o $(NAME) $(FLAGS) $(OBJ)

clean : 
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME) $(OBJ)

re : fclean all

.PHONY : all clean fclean re
