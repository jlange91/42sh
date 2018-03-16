/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 12:25:39 by vmartins          #+#    #+#             */
/*   Updated: 2018/01/25 13:47:43 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/line_edition.h"
#include "../../inc/built_in.h"

static	inline	int	ft_builtins3(t_cmd *cmd, t_termc *tsh)
{
	if (!ft_strcmp(cmd->av[0], "export"))
	{
		prepare_export(cmd);
		return (1);
	}
	else if (!ft_strncmp(cmd->av[0], "theme", 5))
	{
		ft_theme(cmd, tsh);
		return (1);
	}
	else if (!ft_strcmp(cmd->av[0], "history"))
	{
		history(cmd);
		return (1);
	}
	else if (!ft_strcmp(cmd->av[0], "setlocal"))
	{
		prepare_setlocal(cmd);
		return (1);
	}
	return (0);
}

static	inline	int	ft_builtins2(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->av[0], "unsetenv") ||
			!ft_strcmp(cmd->av[0], "unset"))
	{
		ft_prepare_unsetenv(cmd);
		return (1);
	}
	else if (!ft_strcmp(cmd->av[0], "env"))
	{
		ft_env(cmd);
		return (1);
	}
	else if (!ft_strcmp(cmd->av[0], "cd"))
	{
		ft_cd(cmd, 0);
		return (1);
	}
	else if (!ft_strcmp(cmd->av[0], "help"))
	{
		ft_help();
		return (1);
	}
	return (0);
}

int					ft_menu_builtins(t_cmd *cmd, t_termc *tsh)
{
	if (!ft_strcmp(cmd->av[0], "echo"))
	{
		ft_echo(cmd->av);
		return (1);
	}
	else if (!ft_strcmp(cmd->av[0], "pwd"))
	{
		ft_pwd(cmd->av);
		return (1);
	}
	else if (!ft_strcmp(cmd->av[0], "setenv"))
	{
		ft_prepare_setenv(cmd);
		return (1);
	}
	else if (ft_builtins2(cmd))
		return (1);
	else if (ft_builtins3(cmd, tsh))
		return (1);
	return (0);
}
