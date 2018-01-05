/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 19:23:41 by stvalett          #+#    #+#             */
/*   Updated: 2018/01/05 13:56:36 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/line_edition.h"
#include "../../inc/built_in.h"
#include "../../inc/globbing.h"
#include "../../inc/quote.h"

int		cd_fast(char *cmd)
{
	DIR		*dir;

	if ((dir = opendir(cmd)))
	{
		closedir(dir);
		return (1);
	}
	return (0);
}

void			ft_cmd(t_cmd *cmd)
{
	t_termc *tsh;

	if (!cmd->av[0] || !cmd->av[0][0])
		return ;
	tsh = ft_ret_tsh(NULL);
	if (cd_fast(cmd->av[0]) == 1)
	{
		ft_cd(cmd, 1);
		return ;
	}
	if (!ft_strcmp(cmd->av[0], "exit"))
	{
		ft_add_file_history(tsh);
		ft_putstr("exit\n");
		exit(0);
	}
	else if (!ft_strcmp(cmd->av[0], "echo"))
		ft_echo(cmd->av);
	else if (!ft_strcmp(cmd->av[0], "pwd"))
		ft_pwd(cmd->av);
	else if (!ft_strcmp(cmd->av[0], "setenv"))
		ft_prepare_setenv(cmd);
	else if (!ft_strcmp(cmd->av[0], "unsetenv") ||
			!ft_strcmp(cmd->av[0], "unset"))
		ft_prepare_unsetenv(cmd);
	else if (!ft_strcmp(cmd->av[0], "env"))
		ft_env(cmd);
	else if (!ft_strcmp(cmd->av[0], "cd"))
		ft_cd(cmd, 0);
	else if(!ft_strcmp(cmd->av[0], "help"))
		ft_help();
	else if(!ft_strcmp(cmd->av[0], "export"))
		prepare_export(cmd);
	else if (!ft_strcmp(cmd->av[0], "history")) //NO EXPANSION LIKE THIS !! !-N
		history(cmd);
	else if (cmd->av[0])
		ft_exec(cmd->av, ft_var_env(NULL));
	//printf("{%d}\n", ft_singleton(0,0));
}

void			ft_cmd_pipe(t_cmd *cmd)
{
	t_termc *tsh;

	if (!cmd->av[0] || !cmd->av[0][0])
		exit(0);
	tsh = ft_ret_tsh(NULL);
	if (cd_fast(cmd->av[0]) == 1)
	{
		ft_cd(cmd, 1);
		exit(ft_singleton(0,0));
	}
	if (!ft_strcmp(cmd->av[0], "exit"))
	{
		ft_add_file_history(tsh);
		ft_putstr("exit\n");
		exit(0);
	}
	else if (!ft_strcmp(cmd->av[0], "echo"))
		ft_echo(cmd->av);
	else if (!ft_strcmp(cmd->av[0], "pwd"))
		ft_pwd(cmd->av);
	else if (!ft_strcmp(cmd->av[0], "setenv"))
		ft_prepare_setenv(cmd);
	else if (!ft_strcmp(cmd->av[0], "unsetenv") ||
			!ft_strcmp(cmd->av[0], "unset"))
		ft_prepare_unsetenv(cmd);
	else if (!ft_strcmp(cmd->av[0], "env"))
		ft_env(cmd);
	else if (!ft_strcmp(cmd->av[0], "cd"))
		ft_cd(cmd, 0);
	else if(!ft_strcmp(cmd->av[0], "help"))
		ft_help();
	else if(!ft_strcmp(cmd->av[0], "export"))
		prepare_export(cmd);
	else if (!ft_strcmp(cmd->av[0], "history")) //NO EXPANSION LIKE THIS !! !-N
		history(cmd);
	else if (cmd->av[0])
		ft_exec_pipe(cmd->av, ft_var_env(NULL));
	exit(ft_singleton(0,0));
	//printf("{%d}\n", ft_singleton(0,0));
}

void			ft_pipe(t_cmd *cmd);

void	ft_multi_pipe(t_cmd *cmd, int opt)
{
	ft_singleton(0, 1);

	if (opt == 1)
	{
		if (cmd->r_op == 4)
			ft_pipe(cmd);
		ft_redirection(cmd);
		ft_cmd_pipe(cmd);
	}
	else
	{
		ft_redirection(cmd);
		ft_cmd_pipe(cmd);
	}
}

void			ft_pipe(t_cmd *cmd)
{
	int const	READ_END = 0;
	int const	WRITE_END = 1;
	pid_t		child = -1;
	int			pdes[2];

	pipe(pdes);
	child = fork();
	if (child == -1)
	{
		close(pdes[0]);
		close(pdes[1]);
		ft_perror("fork", errno, NULL);
		exit(1);
	}
	else if (child == 0)
	{
		dup2(pdes[WRITE_END], STDOUT_FILENO);
		close(pdes[READ_END]);
		ft_multi_pipe(cmd, 0);
		ft_cmd_pipe(cmd);
		exit(ft_singleton(0, 0));
	}
	else
	{
		dup2(pdes[READ_END], STDIN_FILENO);
		close(pdes[WRITE_END]);
		wait(NULL);
		ft_multi_pipe(cmd->next, 1);
	}
}


int	ft_line_edition(t_cmd *cmd)
{
	pid_t		child = -1;

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
		wait(NULL);
		return (ft_singleton(0,0));
	}
	ft_redirection(cmd);
	ft_cmd(cmd);
	ft_remove_redirection(cmd);
	return (ft_singleton(0, 0));
}
