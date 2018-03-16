/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 12:58:14 by vmartins          #+#    #+#             */
/*   Updated: 2018/02/27 11:21:52 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/line_edition.h"
#include "../../inc/built_in.h"
#include "../../inc/globbing.h"
#include "../../inc/quote.h"

void		ft_cmd(t_cmd *cmd)
{
	t_termc *tsh;

	if (!cmd->av[0] || !cmd->av[0][0])
		return ;
	tsh = ft_ret_tsh(NULL);
	if (!ft_strcmp(cmd->av[0], "exit"))
		ft_exit(cmd);
	else if (!ft_menu_builtins(cmd, tsh))
	{
		if (cmd->av[0])
			ft_exec(cmd, cmd->av, ft_var_env(NULL));
	}
	update_export(-1, -1);
	update_local(-1, -1);
}

void		ft_cmd_pipe(t_cmd *cmd)
{
	t_termc *tsh;

	if (!cmd->av[0] || !cmd->av[0][0])
		exit(0);
	tsh = ft_ret_tsh(NULL);
	if (!ft_strcmp(cmd->av[0], "exit"))
		ft_exit(cmd);
	else if (!ft_menu_builtins(cmd, tsh))
	{
		if (cmd->av[0])
			ft_exec_pipe(cmd->av, ft_var_env(NULL));
	}
	update_export(-1, -1);
	update_local(-1, -1);
	exit(ft_singleton(0, 0));
}

int			ft_builtin_and_exec2(t_cmd *cmd)
{
	if (ft_redirection(cmd) == -1)
	{
		ft_remove_redirection(cmd);
		ft_singleton(1, 1);
		return (1);
	}
	return (0);
}

int			ft_builtin_and_exec(t_cmd *cmd)
{
	ft_singleton(0, 1);
	if (cmd->r_op == 4)
	{
		ft_start_pipe(cmd);
		return (ft_singleton(0, 0));
	}
	if (ft_builtin_and_exec2(cmd))
		return (1);
	ft_cmd(cmd);
	ft_remove_redirection(cmd);
	return (ft_singleton(0, 0));
}
