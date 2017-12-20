/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valide_select.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebrito <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 11:37:49 by adebrito          #+#    #+#             */
/*   Updated: 2017/12/18 16:49:03 by adebrito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	read_text(int fd)
{
	char	buff[120];

	if (fd == -1)
		ft_putstr_fd("FILE NOT FOUND", 2);
	else
	{
		while (read(fd, buff, 1))
			ft_putchar(*buff);
	}
}

void	open_text1(char *str)
{
	int fd;

	if (!ft_strcmp(str, "COPIER/COLLER"))
	{
		fd = open("/tmp/copcol.txt", O_RDONLY);
		read_text(fd);
	}
	if (!ft_strcmp(str, "COUPER/COLLER"))
	{
		fd = open("/tmp/coupcol.txt", O_RDONLY);
		read_text(fd);
	}
	if (!ft_strcmp(str, "SE_DEPLACER"))
	{
		fd = open("/tmp/deplacement.txt", O_RDONLY);
		read_text(fd);
	}
	if (!ft_strcmp(str, "SELECTION"))
	{
		fd = open("/tmp/selection.txt", O_RDONLY);
		read_text(fd);
	}
}

void	open_text2(char *str)
{
	int fd;

	if (!ft_strcmp(str, "AUTOCOMPLETION"))
	{
		fd = open("/tmp/autocompletion.txt", O_RDONLY);
		read_text(fd);
	}
	if (!ft_strcmp(str, "GLOBBING"))
	{
		fd = open("/tmp/globbing.txt", O_RDONLY);
		read_text(fd);
	}
	if (!ft_strcmp(str, "HISTORIQUE"))
	{
		fd = open("/tmp/historique.txt", O_RDONLY);
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
		s->cursor_line = 1;
	while (s->elem[++i].str && i < 10)
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
