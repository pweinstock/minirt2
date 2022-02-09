NAME=miniRT.out

SRC=./hit.c\
		./light.c\
		./main.c\
		./plot_scene.c\
		./ray_color.c\
		./bit_map.c\
		./hooks.c\
		./free_all.c\
		./make_image.c

# -fsanitize=address -fsanitize=thread

LIB = 	./.minilibx_macos/libmlx.a ./parser/parser.a ./libcam/libcam.a ./libmat/libmat.a ./libmath/libmath.a ./shapes/shapes.a ./libray/libray.a ./libvec/libvec.a

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror -O2

MLXFLAGS = -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(LIB) $(OBJ) world.h bit_map.h
	cc $(LIB) $(OBJ) $(FLAGS) $(MLXFLAGS) -o $(NAME)

$(LIB):
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

re: clean all