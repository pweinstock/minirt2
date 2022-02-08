NAME=a.out

SRC=./hit.c\
		./light.c\
		./main.c\
		./plot_scene.c\
		./ray_color.c\
		./bit_map.c\
		./hooks.c\
		./free_all.c\
		./make_image.c


FLAGS = -Wall -Wextra -Werror -O2
# -fsanitize=address -fsanitize=thread

MLXFLAGS =	./.minilibx_macos/libmlx.a -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): lib $(OBJ)
	gcc ./parser/parser.a ./libcam/libcam.a ./libmat/libmat.a ./libmath/libmath.a ./shapes/shapes.a ./libray/libray.a ./libvec/libvec.a $(SRC) $(FLAGS) $(MLXFLAGS)
#	./a.out test1.rt

lib:
	make -C ./parser
	make -C ./libcam
	make -C ./libmat
	make -C ./libmath
	make -C ./libray
	make -C ./libvec
	make -C ./shapes


clean:
	rm -f ./a.out
	make clean -C ./parser
	make clean -C ./libcam
	make clean -C ./libmat
	make clean -C ./libmath
	make clean -C ./libray
	make clean -C ./libvec
	make clean -C ./shapes

fclean: clean
	make fclean -C ./parser
	make fclean -C ./libcam
	make fclean -C ./libmat
	make fclean -C ./libmath
	make fclean -C ./libray
	make fclean -C ./libvec
	make fclean -C ./shapes

re: clean all