/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 18:26:11 by jlange            #+#    #+#             */
/*   Updated: 2017/11/03 19:15:38 by jlange           ###   ########.fr       */
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

void					ft_pwd(t_shell *sh)
{
	char	pwd[PATH_MAX];
	int		flags;

	flags = 0;
	if (init_flags(sh->av, &flags) == -1)
	{
		ft_putstr_fd("pwd: usage: pwd [-LP]\n", 2);
		ft_singleton(1, 1);		
		return ;
	}
	if (flags == 0)
		ft_putendl(sh->pwd);
	else
	{
		getcwd(pwd, sizeof(pwd));
		ft_putendl(pwd);
	}
}
