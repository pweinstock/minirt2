CC=cc

SRC=./set_face_normal.c\
	./sphere.c\
	./plane.c \
	./cylinder.c\
	./transphere.c\
	./cone.c\
	./matrix.c\
	./fill_t_p.c\
	./matrix_init.c

OBJ = $(SRC:.c=.o)

CFLAGS += -Wall -Wextra -Werror

NAME = shapes.a

LIB = ../libray/libray.a ../libmat/libmat.a

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
		ar rcs $(NAME)  $(OBJ)

$(LIB):
	make -C ../libray
	make -C ../libmat

clean :
	rm -f $(OBJ)
	make clean -C ../libray
	make clean -C ../libmat

fclean :	clean
	rm -f $(NAME)
	make fclean -C ../libray
	make fclean -C ../libmat

re : fclean $(NAME)

.PHONY:	all clean fclean re