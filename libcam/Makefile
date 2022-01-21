CC=gcc

SRC=./get_ray.c\
	./set_cam.c\

OBJ = $(SRC:.c=.o)

CFLAGS += -Wall -Wextra -Werror

NAME = libcam.a

all: $(NAME)

$(NAME): ../libray/libray.a ../libmath/libmath.a ../libvec/libvec.a $(OBJ)
		ar rcs  $(NAME) $(OBJ) ../libray/libray.a ../libmath/libmath.a

../libray/libray.a:
	make -C ../libray

../libmath/libmath.a:
	make -C ../libmath

../libvec/libvec.a:
	make -C ../libvec

clean :
	rm -f $(OBJ)

fclean :	clean
	rm -f $(NAME)

re : fclean $(NAME)

.PHONY:	all clean fclean re