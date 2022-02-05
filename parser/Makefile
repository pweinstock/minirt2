CC=gcc

SRC =	./parser.c \
		./parser_helper.c \
		./parser_utils.c \
		./light.c \
		./camera.c \
		./object.c \
		./libft/ft_atoi.c \
		./libft/ft_isdigit.c \
		./libft/ft_split.c \
		./libft/ft_split_space.c \
		./libft/ft_strlen.c \
		./libft/ft_substr.c \
		./get_next_line/get_next_line.c \
#		get_next_line/get_next_line.h \

OBJ = $(SRC:.c=.o)

CFLAGS += -Wall -Wextra -Werror

NAME = parser.a

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

clean :
	rm -f $(OBJ)

fclean :	clean
	rm -f $(NAME)

re : fclean $(NAME)
