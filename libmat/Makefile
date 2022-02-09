CC=cc

SRC=./dielectric.c\
	./helper.c\
	./lambertian.c\
	./metal.c\
	./light.c\
	./emitted.c

OBJ = $(SRC:.c=.o)

CFLAGS += -Wall -Wextra -Werror

NAME = libmat.a

LIB = ../libray/libray.a

all: $(NAME)

$(NAME): $(LIB) $(OBJ) mat.h material.h
		ar rcs  $(NAME) $(OBJ) ../libray/libray.a

$(LIB):
	make -C ../libray

clean :
	rm -f $(OBJ)
	make clean -C ../libray

fclean :	clean
	rm -f $(NAME)
	make fclean -C ../libray

re : fclean $(NAME)

.PHONY:	all clean fclean re