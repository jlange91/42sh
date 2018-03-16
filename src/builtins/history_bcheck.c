/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_bcheck.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:32:14 by vmartins          #+#    #+#             */
/*   Updated: 2018/01/22 16:34:10 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"
#include "../../inc/built_in.h"
#include "../../inc/line_edition.h"

static	inline	int		ft_band_opt(char *av)
{
	int					i;
	int					a;
	int					w;
	int					r;

	w = 0;
	a = 0;
	r = 0;
	i = 0;
	while (av[i])
	{
		if (av[i] == 'w')
			w = 1;
		if (av[i] == 'a')
			a = 1;
		if (av[i] == 'r')
			r = 1;
		i++;
	}
	if ((a && w) || (a && r) || (w && r))
		return (1);
	return (0);
}

int						ft_error_history(char *av, int flag)
{
	ft_putstr_fd("42sh: history: ", 2);
	if (flag == 3)
	{
		ft_putendl_fd("cannot use more than one of -arw", 2);
		return (1);
	}
	if (flag == 1 || flag == 2)
	{
		ft_putchar_fd('-', 2);
		ft_putchar(av[0]);
	}
	else if (flag == 0 || flag == 4)
		ft_putstr_fd(av, 2);
	if (flag == 0)
		ft_putendl_fd(": history position out of range", 2);
	else if (flag == 4)
	{
		ft_putendl_fd(": numeric argument required", 2);
		return (1);
	}
	else
		ft_split_error_hist(flag);
	return (1);
}

static	inline	int		ft_check_other_opt(char *av, int *ret)
{
	int					i;

	i = 0;
	while (av[i])
	{
		if (av[i] == 'd')
		{
			if (av[i + 1] == 0)
				return (-1);
			else
				return (-2);
		}
		if (av[i] != 'c' && av[i] != 'p' && av[i] != 'r' &&
				av[i] != 'w' && av[i] != 'a' && av[i] != 's')
		{
			*ret += i;
			return (i);
		}
		i++;
	}
	return (0);
}

static	int				ft_split_check_opt(char *av1, char *av2, int i, int ret)
{
	int					res;

	res = 0;
	res = ft_check_other_opt(&av1[i], &ret);
	if (res == -1 && !av2)
		return (ft_error_history(&av1[i], 2));
	else if (res == -2)
		return (0);
	else if (res > 0)
		return (ft_error_history(&av1[ret], 1));
	return (-1);
}

int						ft_check_option(char *av1, char *av2)
{
	int					i;
	int					ret;
	int					res;

	i = 0;
	while (av1[++i])
	{
		ret = i;
		if (av1[i] == 'c' || av1[i] == 'p' || av1[i] == 's' || av1[i] == 'd')
		{
			res = ft_split_check_opt(av1, av2, i, ret);
			if (res == 0 || res == 1)
				return (res);
		}
		else if (av1[i] == 'w' || av1[i] == 'r' || av1[i] == 'a')
		{
			if (ft_check_other_opt(&av1[i], &ret))
				return (ft_error_history(&av1[ret], 1));
			else if (ft_band_opt(&av1[i]))
				return (ft_error_history(&av1[ret], 3));
		}
		else
			return (ft_error_history(&av1[ret], 1));
	}
	return (0);
}
