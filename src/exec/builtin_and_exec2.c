/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtiin_and_exec2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebrito <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 16:50:03 by adebrito          #+#    #+#             */
/*   Updated: 2018/01/25 17:19:58 by adebrito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/line_edition.h"
#include "../../inc/built_in.h"
#include "../../inc/globbing.h"
#include "../../inc/quote.h"

void			ft_pipe2(int pdes[2], t_cmd *cmd, int const readend, \
		int const writeend)
{
	dup2(pdes[readend], STDIN_FILENO);
	close(pdes[writeend]);
	if (cmd->r_op != 4)
		wait(NULL);
	ft_multi_pipe(cmd->next, 1);
}

void			ft_pipebis(int pdes[2], t_cmd *cmd, int const readend, \
		int const writeend)
{
	dup2(pdes[writeend], STDOUT_FILENO);
	close(pdes[readend]);
	ft_multi_pipe(cmd, 0);
}

void			ft_pipe(t_cmd *cmd)
{
	int			readend;
	int			writeend;
	pid_t		child;
	int			pdes[2];

	readend = 0;
	writeend = 1;
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
	{
		ft_pipebis(pdes, cmd, readend, writeend);
		exit(ft_singleton(0, 0));
	}
	else
		ft_pipe2(pdes, cmd, readend, writeend);
}
