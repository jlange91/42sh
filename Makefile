# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stvalett <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/30 16:19:42 by stvalett          #+#    #+#              #
#    Updated: 2018/01/31 14:29:45 by jlange           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : all clean fclean re

NAME = 21sh

CC = gcc


CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

LDFLAGS = -L libft

LDLIBS = -lft

LDCURSE = -lncurses

SRCS = 	src/line_edition/term.c								\
	   	src/line_edition/init.c								\
	   	src/line_edition/init2.c							\
	   	src/line_edition/readline.c							\
	   	src/line_edition/utils_read.c						\
	   	src/line_edition/tools_readline.c					\
		src/line_edition/key.c								\
	   	src/line_edition/action_key.c						\
	   	src/line_edition/action_key2.c						\
	   	src/line_edition/signal.c							\
	   	src/line_edition/move_selection.c					\
	   	src/line_edition/move_word.c						\
	   	src/line_edition/move_up_down.c						\
	   	src/line_edition/move_up_down2.c					\
	   src/line_edition/cpy_cut_dup.c						\
	   src/line_edition/display.c							\
	   src/line_edition/tools_display.c						\
	   src/line_edition/history.c							\
	   src/line_edition/prompt.c							\
	   src/line_edition/history2.c							\
	   src/line_edition/tool.c								\
	   src/line_edition/free.c								\
	   src/quote/check.c									\
	   src/quote/count1.c									\
	   src/quote/count2.c									\
	   src/quote/fill.c										\
	   src/quote/fill_line.c								\
	   src/quote/main_quote.c								\
	   src/quote/tools.c									\
	   src/quote/read_quote.c								\
	   src/autocompletion/init_autocompletion.c				\
	   src/autocompletion/init_autocompletion2.c			\
	   src/autocompletion/print_autocompletion.c			\
	   src/autocompletion/tool_print_autocompletion.c		\
	   src/autocompletion/auto_completion.c					\
	   src/autocompletion/auto_completion_key.c				\
	   src/autocompletion/tool_autocompletion.c				\
	   src/autocompletion/tool2_autocompletion.c			\
	   src/autocompletion/multi_choice_autocompletion.c		\
	   src/autocompletion/update_cursor.c					\
	   src/autocompletion/multi_pages.c						\
	   src/autocompletion/print.c							\
	   src/globbing/main_glob.c								\
	   src/globbing/check_glob.c							\
	   src/globbing/tool_glob.c								\
	   src/globbing/open_glob.c								\
	   src/globbing/result_glob.c							\
	   src/globbing/match_chunk.c							\
	   src/globbing/match.c									\
	   src/globbing/tool_match_and_chunk.c					\
	   src/perror/ft_perror.c								\
	   src/perror/error.c									\
	   src/perror/ft_useless_norme.c						\
	   src/builtins/builtins.c								\
	   src/builtins/cd.c									\
	   src/builtins/cd2.c									\
	   src/builtins/cdpath.c								\
	   src/builtins/echo.c									\
	   src/builtins/echo2.c									\
	   src/builtins/env.c									\
	   src/builtins/env2.c									\
	   src/builtins/setenv.c								\
	   src/builtins/unsetenv.c								\
	   src/builtins/pwd.c									\
	   src/builtins/ft_help.c								\
	   src/builtins/export.c								\
	   src/builtins/export2.c								\
	   src/builtins/export3.c								\
	   src/builtins/tools_export.c							\
	   src/builtins/history_b.c								\
	   src/builtins/history_b2.c							\
	   src/builtins/history_bcheck.c						\
	   src/builtins/tool_history.c							\
	   src/replace/replace_to_line.c						\
	   src/replace/ft_replace.c								\
	   src/replace/replace_globbing.c						\
	   src/replace/replace_history.c						\
	   src/replace/tools_replace.c							\
	   src/replace/tools_replace2.c							\
	   src/replace/research_hist.c							\
	   src/replace/ft_replace_dollar.c						\
	   src/replace/ft_replace_tilde.c						\
	   src/replace/ft_replace_line.c						\
	   src/replace/ft_add_escape.c							\
	   src/exec/ft_exec.c									\
	   src/exec/builtin_and_exec.c							\
	   src/exec/ft_exec_pipe.c								\
	   src/exec/ft_exit_exec.c								\
	   src/exec/hash.c										\
	   src/other/charcat.c									\
	   src/other/free_tab_2d.c								\
	   src/other/tab_2d_len.c								\
	   src/other/ft_cp_env.c								\
	   src/other/ft_fill_env.c								\
	   src/other/ft_display_env.c							\
	   src/other/ft_getenv.c								\
	   src/other/ft_replace_env.c							\
	   src/other/ft_remove_useless_path.c					\
	   src/other/ft_replace_str.c							\
	   src/other/ft_chdir_error.c							\
	   src/other/ft_skip_useless.c							\
	   src/other/ft_skip_quote.c							\
	   src/other/singleton.c								\
	   src/other/hash.c										\
	   src/other/ft_backslash_word.c						\
	   src/other/ft_reinit_hash.c							\
	   src/redirection/count.c								\
	   src/redirection/fill_word.c							\
	   src/redirection/ft_ret_word.c						\
	   src/redirection/ft_redirection.c						\
	   src/redirection/backup.c								\
	   src/redirection/ft_remove_redirection.c				\
	   src/redirection/type_redir.c							\
	   src/redirection/ft_redirr_type.c						\
	   src/ft_fill_cmd.c									\
	   src/heredoc/read_heredoc.c							\
	   src/heredoc/tool_heredoc.c							\
	   src/main.c 											\
	   src/free2.c											\
	   src/builtins/ft_theme.c								\
	   src/builtins/ft_theme2.c								\
	   src/line_edition/init3.c								\
	   src/check/ft_check_cmd.c								\
	   src/check/ft_check_redir.c							\
	   src/builtins/ft_local.c								\
	   src/other/singleton2.c								\
	   src/builtins/tools.c									\
	   src/other/update_export.c							\
	   src/exec/builtin_and_exec2.c							\

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
	@make clean -C help_master
	@rm -rf $(OBJ)
	@echo OBJ FROM 42SH REMOVE
	@sleep 2

fclean : clean
	@make fclean -C libft
	@make fclean -C help_master
	@rm -f $(NAME)
	@echo BINAIRE 42SH REMOVE
	@sleep 2

re : fclean all
