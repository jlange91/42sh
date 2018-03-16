/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:32:06 by vmartins          #+#    #+#             */
/*   Updated: 2018/01/22 16:39:32 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"
#include "../../inc/built_in.h"
#include "../../inc/line_edition.h"

int				ft_split_exec(char *av1, int i, char **av, t_hist *hist)
{
	if (av1[i] == 'p')
	{
		if (ft_end(av1, 1))
			return (1);
		else if (av && av[2] != NULL)
			ft_opt_p(av, hist);
	}
	if (av1[i] == 's')
	{
		if (ft_end(av1, 2))
			return (1);
		else if (av && av[2] != NULL)
			ft_opt_s(av, hist);
	}
	return (0);
}

int				ft_split_error_hist(int flag)
{
	if (flag == 2)
		ft_putendl_fd(": option requires an argument", 2);
	else
		ft_putendl_fd(": invalid option", 2);
	ft_putstr_fd("42sh: history: ", 2);
	ft_putstr_fd("usage: ", 2);
	ft_putstr_fd("history [-c] [-d offset] [n] or history -awr", 2);
	ft_putendl_fd("[filename] or history -ps arg [arg...]", 2);
	return (0);
}

int				ft_display_history(t_hist *histlist)
{
	t_history	*begin;
	t_history	*tmp;
	int			i;

	if ((begin = histlist->begin) == NULL)
		return (1);
	tmp = histlist->begin;
	i = 0;
	while (tmp)
	{
		if (tmp->print)
			tmp->index = ++i;
		tmp = tmp->next;
	}
	while (begin)
	{
		if (begin->print)
		{
			ft_putnbr(begin->index);
			ft_putchar(' ');
			ft_putendl(begin->data);
		}
		begin = begin->next;
	}
	return (0);
}

void			ft_del_elem_history_split(int index, t_hist *histlist)
{
	t_history	*tmp;

	tmp = histlist->begin;
	while (tmp)
	{
		if (tmp->index == index)
		{
			tmp->print = 0;
			while (tmp)
			{
				if (tmp->index != 1)
					tmp->index--;
				tmp = tmp->next;
			}
			break ;
		}
		tmp = tmp->next;
	}
}

int				ft_del_elem_history(char *av, t_hist *histlist, int flag)
{
	int			index;
	int			i;

	if (flag == 0)
	{
		i = (av[0] == 'd') ? 1 : 0;
		index = ft_atoi(&av[i]);
		if (!ft_only_digit(&av[i + 1]))
			return (ft_error_history(&av[i], 0));
		else if (index < histlist->begin->index || index > histlist->end->index)
			return (ft_error_history(&av[i], 0));
		else
			ft_del_elem_history_split(index, histlist);
	}
	else
	{
		ft_free_history(histlist);
		histlist->ecrase_hist = 1;
	}
	return (0);
}
