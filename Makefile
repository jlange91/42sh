# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlange <jlange@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/31 11:29:38 by stvalett          #+#    #+#              #
#    Updated: 2017/11/17 03:11:18 by jlange           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : all clean fclean re

NAME = 42sh

CC = gcc


CFLAGS = -Wall -Wextra -Werror -g

LDFLAGS = -L libft

LDLIBS = -lft

LDCURSE = -lncurses

SRCS = src/line_edition/line_edition.c\
	   src/line_edition/term.c\
	   src/line_edition/init.c\
	   src/line_edition/readline.c\
	   src/line_edition/utils_read.c\
	   src/line_edition/tools_readline.c\
	   src/line_edition/key.c\
	   src/line_edition/key2.c\
	   src/line_edition/signal.c\
	   src/line_edition/move_selection.c\
	   src/line_edition/move_word.c\
	   src/line_edition/move_up_down.c\
	   src/line_edition/cpy_cut_dup.c\
	   src/line_edition/display.c\
	   src/line_edition/history.c\
	   src/line_edition/prompt.c\
	   src/line_edition/history2.c\
	   src/line_edition/tool.c\
	   src/quote/check.c\
	   src/quote/count1.c\
	   src/quote/count2.c\
	   src/quote/fill.c\
	   src/quote/fill_line.c\
	   src/quote/main_quote.c\
	   src/quote/tools.c\
	   src/autocompletion/init_autocompletion.c\
	   src/autocompletion/init_autocompletion2.c\
	   src/autocompletion/print_autocompletion.c\
	   src/autocompletion/tool_print_autocompletion.c\
	   src/autocompletion/auto_completion.c\
	   src/autocompletion/auto_completion_key.c\
	   src/autocompletion/tool_autocompletion.c\
	   src/autocompletion/tool2_autocompletion.c\
	   src/autocompletion/multi_choice_autocompletion.c\
	   src/autocompletion/update_cursor.c\
	   src/autocompletion/multi_pages.c\
	   src/globbing/init_glob.c\
	   src/globbing/get_glob.c\
	   src/globbing/result_glob.c\
	   src/globbing/match_chunk.c\
	   src/globbing/match.c\
	   src/globbing/tool_match_and_chunk.c\
	   src/globbing/replace.c\
		src/main.c \
	   	src/perror/ft_perror.c				\
		src/perror/error.c					\
		src/perror/ft_useless_norme.c		\
	   	src/builtins/cd.c					\
		src/builtins/cd2.c					\
		src/builtins/echo.c					\
		src/builtins/echo2.c				\
		src/builtins/env.c					\
		src/builtins/env2.c					\
		src/builtins/setenv.c				\
		src/builtins/unsetenv.c				\
		src/builtins/pwd.c					\
		src/replace/ft_replace.c			\
		src/replace/ft_replace_dollar.c		\
		src/replace/ft_replace_tilde.c		\
		src/replace/ft_replace_line.c		\
		src/replace/ft_add_escape.c			\
		src/exec/ft_exec.c					\
		src/other/charcat.c					\
		src/other/free_tab_2d.c				\
		src/other/tab_2d_len.c				\
		src/other/ft_cp_env.c				\
		src/other/ft_fill_env.c				\
		src/other/ft_display_env.c			\
		src/other/ft_getenv.c				\
		src/other/ft_replace_env.c			\
		src/other/ft_remove_useless_path.c	\
		src/other/ft_replace_str.c			\
		src/other/ft_chdir_error.c			\
					
OBJ = $(SRCS:.c=.o) 

all : $(NAME)

OBJ : $(OBJ)
	@$(CC) $(CFLAGS) -c $(SRCS)

$(NAME) : $(OBJ)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS) $(LDLIBS) $(LDCURSE)
	@echo COMPIALTION 21SH OK !!!!

clean :
	@make clean -C libft
	@rm -rf $(OBJ)
	@echo OBJ FROM 42SH REMOVE
	@sleep 2

fclean : clean
	@make fclean -C libft
	@rm -f $(NAME)
	@echo BINAIRE 42SH REMOVE
	@sleep 2

re : fclean all
