/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtiin_and_exec2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 16:50:03 by vmartins          #+#    #+#             */
/*   Updated: 2018/03/07 00:11:02 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/line_edition.h"
#include "../../inc/built_in.h"
#include "../../inc/globbing.h"
#include "../../inc/quote.h"

void			add_pid_in_tab(int pid)
{
	t_shell		*sh;
	int			*new;
	int			i;

	i = 0;
	sh = ft_ret_sh(NULL);
	new = (int*)malloc(sizeof(int) * (sh->pid_size + 1));
	if (!new)
	{
		ft_perror("malloc", errno, NULL);
		exit(1);
	}
	while (sh->pid && i < sh->pid_size)
	{
		new[i] = sh->pid[i];
		++i;
	}
	new[i] = pid;
	sh->pid_size += 1;
	if (sh->pid)
		free(sh->pid);
	sh->pid = new;
}

void			pipe_tmp(t_cmd *cmd, int pdes[2])
{
	if (cmd->r_op == 4)
		dup2(pdes[1], STDOUT_FILENO);
	close(pdes[0]);
	if (ft_redirection(cmd) == -1)
	{
		ft_remove_redirection(cmd);
		exit(ft_singleton(1, 1));
	}
	ft_cmd_pipe(cmd);
	exit(ft_singleton(0, 0));
}

void			ft_pipe(t_cmd *cmd)
{
	pid_t		child;
	int			pdes[2];

	child = -1;
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
		pipe_tmp(cmd, pdes);
	add_pid_in_tab(child);
	if (cmd->r_op == 4)
	{
		dup2(pdes[0], STDIN_FILENO);
		close(pdes[1]);
	}
}

static inline void		init_backup(void)
{
	ft_backup_stdin(1);
	ft_backup_stdout(1);
	ft_backup_stderr(1);
}

void			ft_start_pipe(t_cmd *cmd)
{
	int			i;
	t_shell		*sh;
	int			status;

	i = -1;
	sh = ft_ret_sh(NULL);
	sh->pid = NULL;
	sh->pid_size = 0;
	init_backup();
	while (cmd->r_op == 4)
	{
		ft_pipe(cmd);
		cmd = cmd->next;
	}
	signal(SIGINT, SIG_IGN);
	ft_pipe(cmd);
	wait(NULL);
	ft_remove_redirection();
	while (++i < sh->pid_size)
		waitpid(sh->pid[i], &status, 0);
	free(sh->pid);
	ft_singleton(status, 1);
	signal(SIGINT, ft_handle_signal);
}
