CC=gcc

SRC=./at.c\
	./set_ray.c

OBJ = $(SRC:.c=.o)

CFLAGS += -Wall -Wextra -Werror

NAME = libray.a

all: $(NAME)

$(NAME): ../libvec/libvec.a $(OBJ)
		ar rcs  $(NAME) $(OBJ) ../libvec/libvec.a

../libvec/libvec.a:
	make -C ../libvec

clean :
	rm -f $(OBJ)


fclean :	clean
	rm -f $(NAME)


re : fclean $(NAME)

.PHONY:	all clean fclean re