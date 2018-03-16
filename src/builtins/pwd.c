/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 18:26:11 by jlange            #+#    #+#             */
/*   Updated: 2017/12/20 17:08:34 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"

static inline int		init_flags(char **av, int *flags)
{
	int j;
	int i;
	int error;

	j = 0;
	while (av[++j] && av[j][0] == '-')
	{
		if (av[j][1] == '-' && av[j][2] == '\0')
			return (j + 1);
		i = 0;
		while (av[j][++i])
		{
			error = 0;
			(av[j][i] == 'L') ? (*flags &= 0b0) : (error += 1);
			(av[j][i] == 'P') ? (*flags |= 0b1) : (error += 1);
			if (error == 2)
				return (-1);
		}
	}
	return (j);
}

void					ft_pwd(char **av)
{
	char	pwd[PATH_MAX];
	int		flags;

	flags = 0;
	if (init_flags(av, &flags) == -1)
	{
		ft_putstr_fd("pwd: usage: pwd [-LP]\n", 2);
		ft_singleton(1, 1);
		return ;
	}
	if (flags == 0)
		ft_putendl(ft_var_pwd(NULL));
	else
	{
		getcwd(pwd, sizeof(pwd));
		ft_putendl(pwd);
	}
}
