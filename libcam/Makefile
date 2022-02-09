CC=cc

SRC=./get_ray.c\
	./setcam.c

OBJ = $(SRC:.c=.o)

CFLAGS += -Wall -Wextra -Werror

NAME = libcam.a

LIB = ../libray/libray.a ../libmath/libmath.a ../libvec/libvec.a

all: $(NAME)

$(NAME): $(LIB) $(OBJ) cam.h
		ar rcs  $(NAME) $(OBJ) $(LIB)

$(LIB):
	make -C ../libray
	make -C ../libmath
	make -C ../libvec

clean :
	rm -f $(OBJ)
	make clean -C ../libray
	make clean -C ../libmath
	make clean -C ../libvec

fclean :	clean
	rm -f $(NAME)
	make fclean -C ../libray
	make fclean -C ../libmath
	make fclean -C ../libvec

re : fclean $(NAME)

.PHONY:	all clean fclean re