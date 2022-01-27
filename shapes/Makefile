CC=gcc

SRC=./set_face_normal.c\
	./sphere.c\
	./plane.c \
	./cylinder.c\
	./transphere.c\
	./cone.c\
	./matrix.c

OBJ = $(SRC:.c=.o)

CFLAGS += -Wall -Wextra -Werror

NAME = shapes.a

all: $(NAME)

$(NAME): ../libray/libray.a ../libmat/libmat.a $(OBJ)
		libtool -static -o $(NAME)  $(OBJ)

# ../libmat/libmat.a ../libray/libray.a

../libray/libray.a:
	make -C ../libray

../libmat/libmat.a:
	make -C ../libmat

clean :
	rm -f $(OBJ)

fclean :	clean
	rm -f $(NAME)

re : fclean $(NAME)

.PHONY:	all clean fclean re