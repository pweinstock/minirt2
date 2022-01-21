NAME=a.out

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): lib
	gcc $(FLAGS) ./libmat/libmat.a ./libcam/libcam.a ./libmath/libmath.a ./libvec/libvec.a ./shapes/shapes.a ./libray/libray.a main.c -o $(NAME)

lib:
	make -C ./libcam
	make -C ./libmat
	make -C ./libmath
	make -C ./libray
	make -C ./libvec
	make -C ./shapes


clean:
	rm -f ./a.out
	make clean -C ./libcam
	make clean -C ./libmat
	make clean -C ./libmath
	make clean -C ./libray
	make clean -C ./libvec
	make clean -C ./shapes

fclean: clean
	make fclean -C ./libcam
	make fclean -C ./libmat
	make fclean -C ./libmath
	make fclean -C ./libray
	make fclean -C ./libvec
	make fclean -C ./shapes

re: clean all