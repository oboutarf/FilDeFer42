# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/31 12:27:59 by oboutarf          #+#    #+#              #
#    Updated: 2022/10/31 12:52:35 by oboutarf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ----------------------------- EXECUTABLE NAME ------------------------------ #

NAME 				= fdf

# -------------------------------- COMPILATION ------------------------------- #

SRCS				= ../main/main.c

OBJS				= *.o

INIT_OBJS			= -o

GCC&FLAGS			= gcc -Wall -Wextra -Werror

SRCH_INCLD			= -I../incld/fdf.h

CONVERT_C_FILES		= -c

# ---------------------------------- CLEAN ----------------------------------- #

RM					= rm -f

# ---------------------------------- COLORS ---------------------------------- #

BI_PURPLE			= '\033[1;95m'

BI_CYAN				= '\033[1;96m'

NC					= '\033[0m'

all: 				$(NAME)

$(NAME):			$(OBJS)
					@$(GCC&FLAGS) $(INIT_OBJS) $(NAME) $(OBJS)

$(OBJS): 			$(SRCS)
					@echo "$(BI_PURPLE)COMPILING....$(NC)\n"
					@$(GCC&FLAGS) -g3 $(CONVERT_C_FILES) $(SRCH_INCLD) $(SRCS)
					@echo "$(BI_CYAN)DONE COMPILING!$(NC)\n\n$(BI_PURPLE)ENJOY!$(NC)\n"

clean:
					@echo "$(BI_PURPLE)REMOVING OBJECTS....$(NC)\n"
					@$(RM) $(OBJS)
					@echo "$(BI_CYAN)OBJECTS REMOVED!$(NC)\n"

fclean:				clean
					@echo "$(BI_PURPLE)REMOVINGS OBJECTS && NAME....$(NC)\n"
					@$(RM) $(NAME)
					@echo "$(BI_CYAN)OBJECTS && NAME REMOVED!$(NC)\n"

re:					fclean $(NAME)

.PHONY: 			all clean fclean re norm