# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/01 15:10:37 by oboutarf          #+#    #+#              #
#    Updated: 2022/11/22 19:59:15 by oboutarf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= fdf42

CC 			= gcc

SRCS		= main/main.c srcs/read/read.c \
			  srcs/read/split.c srcs/print/print.c srcs/draw/drawing_pixels.c \
			  gnl/get_next_line.c gnl/get_next_line_utils.c \

DEBUG_INFO  = -g3 

OBJ			= $(SRCS:.c=.o)

RM			= rm -rf


all:		$(NAME)

%.o: %.c
			$(CC) $(DEBUG_INFO) -Wall -Wextra -Werror -Iincld -Imlx -c $< -o $@

$(NAME): 	$(OBJ)
			make -C mlx
			$(CC) $(OBJ) mlx/libmlx.a -Lmlx -Imlx -lXext -lX11 -lm -o $(NAME)


clean:
			$(RM) srcs/read/*.o && $(RM) main/*.o
			$(RM) srcs/print/*.o && $(RM) srcs/error/*.o
			$(RM) srcs/draw/*.o
			make clean -C mlx

fclean:		clean
			$(RM) $(NAME)

re:			fclean $(NAME)