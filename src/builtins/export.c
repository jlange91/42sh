/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebrito <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 16:10:40 by adebrito          #+#    #+#             */
/*   Updated: 2017/12/08 16:19:26 by adebrito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"

char	**load_env(char **env)
{
	int		i;
	char	**var;

	i = -1;
	if (!(var = (char **)malloc(sizeof(char*) * (tab_2d_len(env) + 1))))
		return (NULL);
	while (env[++i])
		var[i] = ft_strdup(env[i]);
	var[i] = NULL;
	return (var);
}

void	print_var(t_shell *sh, char **var)
{
	int i;

	i = 1;
	while (sh->av[++i])
	{
		if (ft_getenv(sh->av[i], var) == NULL)
		{
			ft_putstr_fd("export: no such variable ", 2);
			ft_putendl_fd(sh->av[i], 2);
		}
	}
	i = 1;
	while (sh->av[++i])
	{
		if (ft_getenv(sh->av[i], var) != NULL)
		{
			ft_putstr("export ");
			ft_putendl(ft_getenv(sh->av[i], var));
		}
	}
}

void	find_flagp_not1(t_shell *sh)
{
	int i;

	i = 0;
	while (sh->av[++i])
	{
		if (i != 1 && !ft_strcmp(sh->av[i], "-p"))
			ft_putendl_fd("export: not valid in this context: -p", 2);
	}
}

void	export_process(t_shell *sh)
{
	int		i;

	i = 0;
	while (sh->av[++i])
	{
		if (!ft_strchr(sh->av[i], '='))
			export_no_eq(sh, i);
		else
			export_with_eq(sh, i);
	}
}

void	prepare_export(t_shell *sh)
{
	find_flagp_not1(sh);
	if (sh->av[1] == NULL)
		ft_display_env(sh->var);
	else if (!ft_strcmp(sh->av[1], "-p") && sh->av[2] == NULL)
		ft_display_env(sh->var);
	else if (!ft_strcmp(sh->av[1], "-b") && sh->av[2] == NULL)
		ft_putstr_fd("Not valid in this context", 2);
	else if (!ft_strcmp(sh->av[1], "-p") && sh->av[2] != NULL)
		print_var(sh, sh->var);
	else if (!ft_strcmp(sh->av[1], "-b") && sh->av[2] != NULL)
		export_flagb(sh);
	else
		export_process(sh);
}
