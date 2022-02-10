NAME=miniRT

SRC=./hit.c\
	./light.c\
	./main.c\
	./plot_scene.c\
	./ray_color.c\
	./bit_map.c\
	./hooks.c\
	./free_all.c\
	./make_image.c\
	./make_picture.c

LIB = 	./.minilibx_macos/libmlx.a ./parser/parser.a ./libcam/libcam.a ./libmat/libmat.a ./libmath/libmath.a ./shapes/shapes.a ./libray/libray.a ./libvec/libvec.a

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -O2

MLXFLAGS = -framework OpenGL -framework AppKit

all: lib $(NAME)

bonus: all

$(NAME): $(LIB) $(OBJ) world.h bit_map.h
	cc $(LIB) $(OBJ) $(CFLAGS) $(MLXFLAGS) -o $(NAME)

lib:
	make -C ./.minilibx_macos
	make -C ./parser
	make -C ./libcam
	make -C ./libmat
	make -C ./libmath
	make -C ./libray
	make -C ./libvec
	make -C ./shapes


clean:
	rm -f $(NAME)
	make clean -C ./.minilibx_macos
	make clean -C ./parser
	make clean -C ./libcam
	make clean -C ./libmat
	make clean -C ./libmath
	make clean -C ./libray
	make clean -C ./libvec
	make clean -C ./shapes

fclean: clean
	rm -f $(OBJ)
	make fclean -C ./parser
	make fclean -C ./libcam
	make fclean -C ./libmat
	make fclean -C ./libmath
	make fclean -C ./libray
	make fclean -C ./libvec
	make fclean -C ./shapes

re: fclean all