/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valide_select.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebrito <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 11:37:49 by adebrito          #+#    #+#             */
/*   Updated: 2018/01/24 16:05:27 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	read_text(int fd)
{
	char	c;

	if (fd == -1)
		ft_putstr_fd("FILE NOT FOUND", 2);
	else
	{
		c = 0;
		while (read(fd, &c, 1))
			ft_putchar(c);
	}
}

void	open_text1(char *str)
{
	int fd;

	if (!ft_strcmp(str, "COPIER/COLLER"))
	{
		fd = open("/tmp/help_book/cpypast.txt", O_RDONLY);
		read_text(fd);
	}
	if (!ft_strcmp(str, "COUPER/COLLER"))
	{
		fd = open("/tmp/help_book/cutcpy.txt", O_RDONLY);
		read_text(fd);
	}
	if (!ft_strcmp(str, "SE_DEPLACER"))
	{
		fd = open("/tmp/help_book/deplacement.txt", O_RDONLY);
		read_text(fd);
	}
	if (!ft_strcmp(str, "SELECTION"))
	{
		fd = open("/tmp/help_book/selection.txt", O_RDONLY);
		read_text(fd);
	}
}

void	open_text2(char *str)
{
	int fd;

	if (!ft_strcmp(str, "AUTOCOMPLETION"))
	{
		fd = open("/tmp/help_book/autocompletion.txt", O_RDONLY);
		read_text(fd);
	}
	if (!ft_strcmp(str, "GLOBBING"))
	{
		fd = open("/tmp/help_book/globbing.txt", O_RDONLY);
		read_text(fd);
	}
	if (!ft_strcmp(str, "HISTORIQUE"))
	{
		fd = open("/tmp/help_book/history.txt", O_RDONLY);
		read_text(fd);
	}
}

void	ft_valide_select(t_select **select)
{
	int			i;
	t_select	*s;

	s = *select;
	i = -1;
	s->elem[s->cursor_line - 1].select = 1;
	if (s->cursor_line == s->nb_elem)
		s->cursor_line = 0;
	while (s->elem[++i].str && i < 7)
	{
		if (s->elem[i].select == 1)
		{
			tputs(tgetstr("cl", NULL), 1, ft_putc);
			open_text1(s->elem[i].str);
			open_text2(s->elem[i].str);
			s->elem[i].select = 0;
		}
	}
}
