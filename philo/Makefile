# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayassir <ayassir@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/25 11:44:32 by ayassir           #+#    #+#              #
#    Updated: 2022/06/26 18:12:12 by ayassir          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

SRC_M		=	2_functions.c 4_functions.c\
				1_functions.c 3_functions.c\

SRC_P		=	philo.c\

SRC_DIR		=	srcs

OBJDIR		=	other

CFLAGS		=	-Wall -Wextra -Werror -pthread

HEADER		=	philosophers.h

RM			=	rm -rf

WHITE		=	\033[m
RED			=	\033[1;31m
GREEN		=	\033[1;32m
YELLOW		=	\033[1;33m
BLUE		=	\033[1;34m
PURPLE		=	\033[1;35m
CYAN		=	\033[1;36m

OBJ_M		=	$(addprefix $(OBJDIR)/, $(SRC_M:%.c=%.o))
OBJ_P		=	$(SRC_P:.c=.o)


all: $(NAME)

$(NAME): $(OBJ_M) $(OBJ_P)
	@echo "\n$(YELLOW)Building    $(YELLOW)->\t/$(CYAN)$(NAME)$(WHITE)\n"
	@$(CC) $(CFLAGS) $(OBJ_M) $(OBJ_P) -o $(NAME)

$(OBJDIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p Other
	@echo "$(GREEN)Compiling   $(YELLOW)->\t/$(shell basename $<)$(WHITE)"
	@$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.c $(HEADER)
	@echo "$(GREEN)Compiling   $(YELLOW)->\t/$(shell basename $<)$(WHITE)"
	@$(CC) $(CFLAGS) -c -o $@ $<
	
clean:
	@echo "\n$(RED)removing    $(YELLOW)->\t/$(CYAN)$(OBJ_M)$(WHITE)"
	@$(RM) $(OBJ_M)
	@$(RM) $(OBJ_P)

fclean: clean
	@echo "$(RED)removing    $(YELLOW)->\t/$(CYAN)$(NAME)$(WHITE)\n"
	@$(RM) $(NAME)

re: fclean all

mandatory:	$(NAME)

m:			mandatory
b:			bonus

.PHONY: all clean fclean re mandatory m bonus b
