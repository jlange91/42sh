# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmartins <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/24 14:18:08 by vmartins          #+#    #+#              #
#    Updated: 2018/02/13 11:40:45 by vmartins         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = builtin_help

FLAGS = -Wall -Wextra -Werror

SRCS = srcs/main.c \
	   srcs/ft_arrow_key.c \
	   srcs/ft_putc.c \
	   srcs/ft_select.c \
	   srcs/ft_valide_select.c \
	   srcs/keep_term.c \
	   srcs/ft_print_all.c \
	   srcs/ft_read_commande.c \
	   srcs/ft_signal.c \
	   srcs/init_term.c \

INCLUDES = includes/ft_select.h

# COLORS
C_NO = "\033[00m"
C_OK = "\033[35m"
C_GOOD = "\033[32m"
C_ERROR = "\033[31m"
C_WARN = "\033[33m"

# MESSAGE
SUCCESS= $(C_GOOD)SUCCESS$(C_NO)
OK = $(C_OK)OK$(C_NO)

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Compiling Builtin Help"  "..."
	@cp -R help_book /tmp
	@make -C libft/
	@gcc -I includes libft/libft.a -o $(NAME) $(SRCS) -lreadline -ltermcap
	@echo "Compiling Builtin Help" $(SUCCESS)
	@mv $(NAME) /tmp/$(NAME)

%.o: %.c
	@gcc -I includes -o $@ -c $< $(FLAGS)

clean:
	@rm -rf $(OBJ) $(OBJ_MAIN)
	@make clean -C libft/
	@echo "Cleaning..." $(OK)

fclean: clean
	@rm -f $(NAME) /tmp/$(NAME) $(LIB)
	@make fclean -C libft/
	@echo "Delete" $(OK)

re: fclean all

.PHONY: all clean fclean re
