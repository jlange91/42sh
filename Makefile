# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stvalett <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/31 11:29:38 by stvalett          #+#    #+#              #
#    Updated: 2017/11/02 10:27:56 by stvalett         ###   ########.fr        #
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
	   src/line_edition/prompt.c\
	   src/line_edition/display.c\
	   src/line_edition/history.c\
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
	   src/token/lexer.c\
	   src/token/token.c\
	   src/token/utils_token.c\
	   src/tree/tree.c\
	   src/tree/job.c\
	   src/tree/utils_tree.c\
	   src/exec/exec.c\
	   src/exec/cmd.c\
	   src/exec/util_cmd.c\
	   src/env_term/env.c\
	   src/env_term/env_tools.c\
	   src/env_term/init_env.c\
	   src/env_term/getenv.c\
	   src/env_term/free.c\
	   src/built-in/cd.c\
	   src/built-in/env.c\
	   src/built-in/built.c\
	   src/built-in/built_utils.c\
	   src/built-in/ft_cmd_setenv.c\
	   src/built-in/ft_cmd_unsetenv.c \
	   src/built-in/tools_built_in.c \
	   src/built-in/ft_cmd_echo.c \
	   src/built-in/cd_to.c \
	   src/built-in/cd_to_slash.c \
	   src/built-in/tool_for_cd.c \
	   src/built-in/more_tool_for_cd.c \
	   src/main.c
					
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
