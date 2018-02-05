/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 16:10:40 by adebrito          #+#    #+#             */
/*   Updated: 2018/01/25 16:22:12 by adebrito         ###   ########.fr       */
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

void	print_var(t_cmd *cmd)
{
	int	i;

	i = place_me(cmd);
	while (cmd->av[++i])
	{
		if (ft_getenv(cmd->av[i], ft_var_var(NULL)) == NULL)
		{
			ft_putstr_fd("export: no such variable ", 2);
			ft_putendl_fd(cmd->av[i], 2);
		}
	}
	i = 1;
	while (cmd->av[++i])
	{
		if (ft_getenv(cmd->av[i], ft_var_var(NULL)) != NULL &&
				ft_strcmp(cmd->av[i], "-p") && ft_strcmp(cmd->av[i], "-b"))
		{
			ft_putstr("export ");
			ft_putendl(ft_getenv(cmd->av[i], ft_var_var(NULL)));
		}
	}
}

int		find_flagp_not1(t_cmd *cmd, int indicator, int i)
{
	while (cmd->av[++i])
	{
		if (ft_strcmp(cmd->av[i], "-p") && ft_strcmp(cmd->av[i], "-b")
				&& cmd->av[i][0] == '-')
		{
			ft_putendl_fd(" invalid option, only -p and -b can be used", 2);
			return (0);
		}
	}
	i = 0;
	while (cmd->av[++i])
	{
		if (i != 1 && !ft_strcmp(cmd->av[i], "-p") && \
				ft_strcmp(cmd->av[1], "-p"))
			indicator = 1;
	}
	if (indicator == 1)
		ft_putendl_fd("export; -p not valid in this context", 2);
	return (1);
}

int		export_process(t_cmd *cmd)
{
	int		i;
	int		save;

	i = 0;
	save = 0;
	while (cmd->av[++i])
	{
		if (check_pattern(cmd->av[i]) == 0)
		{
			ft_putstr_fd("export: ", 2);
			ft_putstr_fd(cmd->av[i], 2);
			ft_putendl_fd(": not a valid identifier", 2);
			if (cmd->av[2] == NULL)
				return (ft_singleton(1, 1));
		}
		else if (!ft_strchr(cmd->av[i], '='))
			export_no_eq(cmd, i);
		else
		{
			save = export_with_eq(cmd, i);
			if (cmd->av[2] == NULL && save == 1)
				return (ft_singleton(1, 1));
		}
	}
	return (0);
}

void	prepare_export(t_cmd *cmd)
{
	if (only_p(cmd) == 1)
		return ;
	if (find_flagp_not1(cmd, 0, 0) == 1)
	{
		if (cmd->av[1] == NULL)
			ft_display_env(ft_var_var(NULL));
		if (!ft_strcmp(cmd->av[1], "-p") && cmd->av[2] == NULL)
			ft_display_export(ft_var_var(NULL));
		else if (!ft_strcmp(cmd->av[1], "-b") && cmd->av[2] == NULL)
		{
			ft_putendl_fd("Not valid in this context", 2);
			ft_singleton(1, 1);
		}
		else if (!ft_strcmp(cmd->av[1], "-p") && cmd->av[2] != NULL)
			print_var(cmd);
		else if (!ft_strcmp(cmd->av[1], "-b") && cmd->av[2] != NULL)
			export_flagb(cmd, 1);
		else
			export_process(cmd);
	}
	ft_singleton(1, 1);
}
