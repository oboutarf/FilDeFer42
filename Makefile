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

SRCS		= main/main.c srcs/read/get_next_line.c \
			  srcs/read/get_next_line_utils.c srcs/read/read.c \
			  srcs/read/split.c srcs/print/print.c srcs/draw/drawing_pixels.c \

DEBUG_INFO  = -g3

OBJ			= $(SRCS:.c=.o)

RM			= rm -rf


all:		$(MAKE) $(NAME)

$(MAKE):
			make -C mlx

%.o: %.c
			$(CC) -I./incld -I./mlx -L./mlx -lXext -lX11 -lmlx -c $< -o $@

$(NAME): 	$(OBJ)
			$(CC) $(OBJ) -L./mlx -lmlx -I./mlx -lXext -lX11 -o $(NAME)

clean:
			$(RM) srcs/read/*.o && $(RM) main/*.o
			$(RM) srcs/print/*.o && $(RM) srcs/error/*.o
			$(RM) srcs/draw/*.o 
			make clean -C mlx

fclean:		clean
			$(RM) $(NAME)

re:			fclean $(NAME)