/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 18:25:03 by jlange            #+#    #+#             */
/*   Updated: 2017/12/20 17:04:12 by jlange           ###   ########.fr       */
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

void					swap_pwd(int opt)
{
	char *oldpwd;

	if ((oldpwd = ft_getenv("OLDPWD", ft_var_env(NULL))) == NULL || !oldpwd[7])
	{
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
		ft_singleton(1, 1);
		return ;
	}
	if (opt == 1)
		ft_cd_p(&oldpwd[7]);
	else
		ft_cd_l(&oldpwd[7]);
}

void					go_home(int opt)
{
	char	*home;

	if ((home = ft_getenv("HOME", ft_var_env(NULL))) == NULL || !home[5])
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		ft_singleton(1, 1);
		return ;
	}
	if (opt == 1)
		ft_cd_p(&home[5]);
	else
		ft_cd_l(&home[5]);
}

void					ft_cd(t_cmd *cmd)
{
	int		opt;
	int		i;

	opt = 0;
	i = init_flags(cmd->av, &opt, 0);
	if (!cmd->av[i])
		go_home(opt);
	else if (!ft_strcmp(cmd->av[i], "-"))
		swap_pwd(opt);
	else if (opt == 0)
		ft_cd_l(cmd->av[i]);
	else if (opt == 1)
		ft_cd_p(cmd->av[i]);
}
