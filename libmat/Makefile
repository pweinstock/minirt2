CC=gcc

SRC=./dielectric.c\
	./helper.c\
	./lambertian.c\
	./metal.c

OBJ = $(SRC:.c=.o)

CFLAGS += -Wall -Wextra -Werror

NAME = libmat.a

all: $(NAME)

$(NAME): ../libray/libray.a $(OBJ)
		ar rcs  $(NAME) $(OBJ) ../libray/libray.a

../libray/libray.a:
	make -C ../libray

clean :
	rm -f $(OBJ)

fclean :	clean
	rm -f $(NAME)

re : fclean $(NAME)

.PHONY:	all clean fclean re