# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlange <jlange@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/31 15:47:13 by stvalett          #+#    #+#              #
#    Updated: 2018/01/05 14:57:02 by jlange           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS = src/ft_memset.c\
	   src/ft_memalloc.c\
	   src/ft_memcpy.c\
	   src/ft_memccpy.c\
	   src/ft_memchr.c\
	   src/ft_memdel.c\
	   src/ft_memmove.c\
	   src/ft_memcmp.c\
	   src/ft_bzero.c\
	   src/ft_strcmp.c\
	   src/ft_strncmp.c\
	   src/ft_isalpha.c\
	   src/ft_isdigit.c\
	   src/ft_only_digit.c\
	   src/ft_isalnum.c\
	   src/ft_isascii.c\
	   src/ft_toupper.c\
	   src/ft_tolower.c\
	   src/ft_isprint.c\
	   src/ft_atoi.c\
	   src/ft_itoa.c\
	   src/ft_strlen.c\
	   src/ft_count_dtab.c\
	   src/ft_putstr.c\
	   src/ft_putstr_fd.c\
	   src/ft_putendl.c\
	   src/ft_putendl_fd.c\
	   src/ft_putchar.c\
	   src/ft_putchar_fd.c\
	   src/ft_putnbr.c\
	   src/ft_putnbr_fd.c\
	   src/count_from_file.c\
	   src/ft_strstr.c\
	   src/ft_strnstr.c\
	   src/ft_strnstr.c\
	   src/ft_strdup.c\
	   src/ft_at_strcpy.c\
	   src/ft_strcpy_to.c\
	   src/ft_strcpy.c\
	   src/ft_strncpy.c\
	   src/ft_strcat.c\
	   src/ft_strncat.c\
	   src/ft_strlcat.c\
	   src/ft_strndup.c\
	   src/ft_strdel.c\
	   src/ft_strclr.c\
	   src/ft_strchr.c\
	   src/ft_strrchr.c\
	   src/ft_strequ.c\
	   src/ft_strnequ.c\
	   src/ft_striter.c\
	   src/ft_striteri.c\
	   src/ft_strjoin.c\
	   src/ft_strmap.c\
	   src/ft_strmapi.c\
	   src/ft_strnew.c\
	   src/ft_strsplit.c\
	   src/ft_strsplit2.c\
	   src/ft_strsub.c\
	   src/ft_strtrim.c\
	   src/ft_strtrim2.c\
	   src/ft_lstnew.c\
	   src/ft_lstmap.c\
	   src/ft_lstdelone.c\
	   src/ft_lstdel.c\
	   src/ft_lstadd.c\
	   src/ft_lstiter.c\
	   src/ft_sqrt.c\
	   src/ft_rot13.c\
	   src/ft_abs.c\
	   src/ft_push_back.c\
	   src/ft_strcapitalize.c\
	   src/ft_free_tab.c\
	   src/get_next_line.c \
	   src/ft_strbchr.c \
	   src/ft_escapequote.c \
	   src/ft_tabtospace.c \
	   src/ft_strtrim_c.c \
	   src/ft_free_join.c \
	   src/ft_tablen.c \
	   src/ft_tabdup.c \
	   src/free_tab.c \
	   src/ft_countword.c \
	   src/ft_return.c \
	   src/ft_count_opendir.c\
	   src/ft_swap.c\
	   src/ft_reverse.c\
	   src/ft_intlen.c\

OBJ = $(SRCS:.c=.o)

INCLUDES = -Ilibft

all : $(NAME)

.SILENT:
OBJ : $(OBJ)
	@$(CC) $(CFLAGS) -c $(SRCS)

$(NAME) : $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo LIBFT.A CREATE

clean :
	@rm -f $(OBJ)
	@echo OBJ FROM LIBFT REMOVE

fclean: clean
	@rm -f $(NAME)
	@echo LIBFT.A FROM LIBFT REMOVE

re : fclean all

.PHONY : clean fclean re
