CC=gcc

SRC=./cross.c\
	./division.c\
	./dot.c\
	./invert.c\
	./length.c\
	./minus.c\
	./multiply.c\
	./plus.c\
	./random.c\
	./random1.c\
	./setvec.c\
	./transmitted.c\
	./unit_vector.c

OBJ = $(SRC:.c=.o)

CFLAGS += -Wall -Wextra -Werror

NAME = libvec.a

all: $(NAME)

$(NAME):$(OBJ)
		ar rcs  $(NAME) $(OBJ)

clean :
		rm -f $(OBJ)

fclean :	clean
		rm -f $(NAME)

re : fclean $(NAME)

.PHONY:	all clean fclean re