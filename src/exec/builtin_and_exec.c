/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 12:58:14 by stvalett          #+#    #+#             */
/*   Updated: 2018/01/25 17:17:44 by adebrito         ###   ########.fr       */
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
	{
		ft_add_file_history(tsh);
		ft_putstr("exit\n");
		exit(0);
	}
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
	{
		ft_add_file_history(tsh);
		ft_putstr("exit\n");
		exit(0);
	}
	else if (!ft_menu_builtins(cmd, tsh))
	{
		if (cmd->av[0])
			ft_exec_pipe(cmd->av, ft_var_env(NULL));
	}
	update_export(-1, -1);
	update_local(-1, -1);
	exit(ft_singleton(0, 0));
}

void		ft_multi_pipe(t_cmd *cmd, int opt)
{
	ft_singleton(0, 1);
	if (opt == 1)
	{
		if (cmd->r_op == 4)
			ft_pipe(cmd);
		if (ft_redirection(cmd) == -1)
		{
			ft_remove_redirection(cmd);
			exit(1);
		}
		ft_cmd_pipe(cmd);
	}
	else
	{
		if (ft_redirection(cmd) == -1)
		{
			ft_remove_redirection(cmd);
			exit(1);
		}
		ft_cmd_pipe(cmd);
	}
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
	pid_t		child;
	int			status;

	child = -1;
	ft_singleton(0, 1);
	if (cmd->r_op == 4)
	{
		child = fork();
		if (child == -1)
		{
			ft_perror("fork", errno, NULL);
			exit(1);
		}
		else if (child == 0)
			ft_pipe(cmd);
		wait(&status);
		if (status)
			ft_singleton(status, 1);
		return (ft_singleton(0, 0));
	}
	if (ft_builtin_and_exec2(cmd))
		return (1);
	ft_cmd(cmd);
	ft_remove_redirection(cmd);
	return (ft_singleton(0, 0));
}
