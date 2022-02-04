# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/22 16:41:24 by pweinsto          #+#    #+#              #
#    Updated: 2022/02/03 12:36:43 by pweinsto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT 

SRCS =	miniRT.c \
		miniRT.h \
		scene.c \
		plot_scene.c \
		RotationMatrix.c \
		vector_math.c \
		color_math.c \
		parser/parser.c \
		parser/get_next_line/get_next_line.c \
		parser/get_next_line/get_next_line.h \
		parser/libft/ft_atoi.c \
		parser/libft/ft_isdigit.c \
		parser/libft/ft_split.c \
		parser/libft/ft_strlen.c \
		parser/libft/ft_substr.c \
		parser/libft/libft.h \


CC		=		gcc

CFLAGS	=		-Wall -Wextra -Werror

MLXFLAGS =		./minilibx_macos/libmlx.a -framework OpenGL -framework AppKit

all:	$(NAME)

$(NAME):
		$(CC) $(CFLAGS) $(MLXFLAGS) $(SRCS)

fclean:
			$(RM) $(NAME)

re:			fclean
