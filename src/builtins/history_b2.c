/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_b2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebrito <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 14:55:30 by adebrito          #+#    #+#             */
/*   Updated: 2018/01/22 16:27:03 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"
#include "../../inc/built_in.h"
#include "../../inc/line_edition.h"

void	ft_opt_a(char *av2, t_history *begin, hlist *hist)
{
	int		fd;
	int		i;

	if (hist->ecrase_hist)
		return ;
	if ((fd = open(av2, (O_WRONLY | O_CREAT | O_APPEND), 0600)) < 0)
		return ;
	if (begin)
	{
		i = 0;
		while (begin)
		{
			if (begin->new && begin->new != 104)
			{
				write(fd, begin->data, ft_strlen(begin->data));
				write(fd, "\n", 1);
			}
			begin = begin->next;
		}
	}
}

void	ft_opt_r(char *av2, t_history *begin, hlist *hist)
{
	int		fd;
	char	*line;
	int		ret;

	(void)begin;
	if ((fd = open(av2, O_RDONLY)) < 0)
		push_backhist(hist, av2, hist->end->index + 1, 1);
	else
	{
		while ((ret = get_next_line(fd, &line)) > 0)
		{
			push_backhist(hist, line, hist->end->index + 1, 104);
			free(line);
		}
	}
}

void	ft_opt_w(char *av2, t_history *begin, hlist *hist)
{
	int		fd;
	int		i;

	(void)hist;
	fd = (hist->ecrase_hist) ? open(av2, (O_WRONLY | O_CREAT | O_TRUNC), 0600) :
		open(av2, (O_WRONLY | O_CREAT | O_APPEND), 0600);
	if (begin)
	{
		i = 0;
		while (begin)
		{
			write(fd, begin->data, ft_strlen(begin->data));
			write(fd, "\n", 1);
			begin = begin->next;
		}
	}
}

int		ft_opt_p(char **av, hlist *hist)
{
	int		i;

	hist->end->print = 0;
	i = 2;
	while (av[i])
	{
		ft_putendl(av[i]);
		i++;
	}
	return (0);
}

int		ft_opt_s(char **av, hlist *hist)
{
	int		i;
	int		len;
	char	*line;

	hist->end->print = 0;
	line = NULL;
	line = ft_strjoin(av[2], " ");
	i = 3;
	len = ft_count_dtab(av);
	while (av[i])
	{
		line = ft_free_join(line, av[i], 'L');
		if (i != len)
			line = ft_free_join(line, " ", 'L');
		i++;
	}
	push_backhist(hist, line, hist->end->index + 1, 1);
	free(line);
	return (0);
}
