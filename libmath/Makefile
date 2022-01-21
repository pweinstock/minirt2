CC=gcc

SRC=./clamp.c\
	./degrees_to_radians.c

OBJ = $(SRC:.c=.o)

CFLAGS += -Wall -Wextra -Werror

NAME = libmath.a

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs  $(NAME) $(OBJ)

clean :
	rm -f $(OBJ)

fclean :	clean
	rm -f $(NAME)

re : fclean $(NAME)

.PHONY:	all clean fclean re