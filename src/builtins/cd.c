/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 18:25:03 by jlange            #+#    #+#             */
/*   Updated: 2017/11/16 13:25:34 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"
#include "../../inc/built_in.h"

static inline int		init_flags(char **av, int *flags, int save)
{
	int j;
	int i;
	int error;

	j = 0;
	while (av[++j] && av[j][0] == '-')
	{
		save = *flags;
		if (av[j][1] == '\0')
			return (j);
		else if (av[j][1] == '-' && av[j][2] == '\0')
			return (j + 1);
		i = 0;
		while (av[j][++i])
		{
			error = 0;
			(av[j][i] == 'L') ? (*flags |= 0b0) : (error += 1);
			(av[j][i] == 'P') ? (*flags |= 0b1) : (error += 1);
			*flags = (error == 2) ? save : *flags;
			if (error == 2)
				return (j);
		}
	}
	return (j);
}

void					swap_pwd(t_shell *sh, int opt)
{
	char *oldpwd;

	if ((oldpwd = ft_getenv("OLDPWD", sh->env)) == NULL || !oldpwd[7])
	{
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
		ft_singleton(1, 1);
		return ;
	}
	if (opt == 1)
		ft_cd_p(sh, &oldpwd[7]);
	else
		ft_cd_l(sh, &oldpwd[7]);
}

void					go_home(t_shell *sh, int opt)
{
	char	*home;

	if ((home = ft_getenv("HOME", sh->env)) == NULL || !home[5])
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		ft_singleton(1, 1);		
		return ;
	}
	if (opt == 1)
		ft_cd_p(sh, &home[5]);
	else
		ft_cd_l(sh, &home[5]);
}

void					ft_cd(t_shell *sh)
{
	int		opt;
	int		i;
	

	opt = 0;
	i = init_flags(sh->av, &opt, 0);
	if (!sh->av[i])
		go_home(sh, opt);
	else if (!ft_strcmp(sh->av[i], "-"))
		swap_pwd(sh, opt);
	else if (opt == 0)
		ft_cd_l(sh, sh->av[i]);
	else if (opt == 1)
		ft_cd_p(sh, sh->av[i]);
}
