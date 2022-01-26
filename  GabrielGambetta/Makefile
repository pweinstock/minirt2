# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/22 16:41:24 by pweinsto          #+#    #+#              #
#    Updated: 2022/01/26 14:25:57 by pweinsto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT 

SRCS =	miniRT.c \
		miniRT.h \
		scene.c \
		plot_scene.c \
		RotationMatrix.c \

CC		=		gcc

CFLAGS	=		-Wall -Wextra -Werror

MLXFLAGS =		./minilibx_macos/libmlx.a -framework OpenGL -framework AppKit

all:	$(NAME)

$(NAME):
		$(CC) $(CFLAGS) $(MLXFLAGS) $(SRCS)

fclean:
			$(RM) $(NAME)

re:			fclean
