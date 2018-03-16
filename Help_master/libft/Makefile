# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmartins <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/22 15:51:53 by vmartins          #+#    #+#              #
#    Updated: 2017/05/29 14:47:41 by vmartins         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memccpy.c \
	ft_memmove.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strlen.c \
	ft_strdup.c \
	ft_strcpy.c \
	ft_strncpy.c \
	ft_strcat.c \
	ft_strncat.c \
	ft_strlcat.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strstr.c \
	ft_strnstr.c \
	ft_strcmp.c \
	ft_strncmp.c \
	ft_atoi.c \
	ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_memalloc.c \
	ft_memdel.c \
	ft_strnew.c \
	ft_strdel.c \
	ft_strdel.c \
	ft_strclr.c \
	ft_striter.c \
	ft_striteri.c \
	ft_strmap.c \
	ft_strmapi.c \
	ft_strequ.c \
	ft_strnequ.c \
	ft_strsub.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_strsplit.c \
	ft_itoa.c \
	ft_putchar.c \
	ft_putstr.c \
	ft_putendl.c \
	ft_putnbr.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_lstnew.c \
	ft_lstdelone.c \
	ft_lstdel.c \
	ft_lstadd.c \
	ft_lstiter.c \
	ft_lstmap.c \
	ft_lst_push_back.c \
	ft_lst_push_front.c \
	ft_free_join.c \
	ft_strtab.c \
	ft_sort_tab.c \
	get_next_line.c \
	ft_strlen2d.c \
	ft_strbchr.c \
	ft_free_tab.c \
	ft_duptab2d.c \
	ft_ctostr.c \
	ft_straddat.c \
	ft_strdelat.c \
	ft_tabbpushback.c \
	ft_tabblen.c \
	ft_tabbcreate.c \
	ft_freetabb.c \
	ft_tabdup.c \
	ft_tablen.c \
	ft_tabpushback.c \
	ft_tabcreate.c \
	ft_strtabb.c \
	ft_freetab.c \
	ft_strtrim_c.c \
	ft_escapequote.c \
	ft_tabtospace.c \
	free_tab.c \

OBJECTS = $(SRCS:.c=.o)

FLAG = -Wall -Werror -Wextra

all: $(NAME)

$(NAME):
	@gcc -c $(FLAG) $(SRCS)
	@ar rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)
	@echo "libft created"

.PHONY: clean
clean:
	@rm -f $(OBJECTS)
	@echo "objects files deleted"

fclean: clean
	@rm -f $(NAME)
	@echo "libft deleted"

re: fclean all
