/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirr_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 16:37:47 by jlange            #+#    #+#             */
/*   Updated: 2018/02/13 11:17:40 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"

void		ft_redirr_type8(t_redir *red)
{
	if (red->in == -1)
		close(1);
	else if (red->in != ft_backup_stdin(0) &&
			red->in != ft_backup_stdout(0) &&
			red->in != ft_backup_stderr(0))
		close(red->in);
}

int			ft_redirr_type1(t_redir *red)
{
	char			*nb;
	struct stat		buf;

	if (red->in == ft_backup_stdin(0) || red->in == ft_backup_stdout(0) ||
		red->in == ft_backup_stderr(0) || red->out == ft_backup_stdin(0) ||
		red->out == ft_backup_stdout(0) || red->out == ft_backup_stderr(0))
	{
		nb = (red->in == ft_backup_stdin(0) || red->in == ft_backup_stdout(0) ||
		red->in == ft_backup_stderr(0)) ? ft_itoa(red->in) : ft_itoa(red->out);
		ft_putstr_fd("shell: protected fd: ", 2);
		ft_putstr_fd(nb, 2);
		write(2, "\n", 1);
		free(nb);
		return (1);
	}
	if (dup2(red->out, (red->in == -1) ? 1 : red->in) == -1)
	{
		nb = ft_itoa((fstat(red->out, &buf) == 0) ? red->in : red->out);
		ft_perror("shell", errno, nb);
		free(nb);
		return (1);
	}
	return (0);
}

int			ft_redirr_type2(t_redir *red)
{
	char			*nb;
	struct stat		buf;

	if (red->in == ft_backup_stdin(0) || red->in == ft_backup_stdout(0) ||
		red->in == ft_backup_stderr(0) || red->out == ft_backup_stdin(0) ||
		red->out == ft_backup_stdout(0) || red->out == ft_backup_stderr(0))
	{
		nb = (red->in == ft_backup_stdin(0) || red->in == ft_backup_stdout(0) ||
		red->in == ft_backup_stderr(0)) ? ft_itoa(red->in) : ft_itoa(red->out);
		ft_putstr_fd("shell: protected fd: ", 2);
		ft_putstr_fd(nb, 2);
		write(2, "\n", 1);
		free(nb);
		return (1);
	}
	if (dup2(red->out, (red->in == -1) ? 0 : red->in) == -1)
	{
		nb = ft_itoa((fstat(red->out, &buf) == 0) ? red->in : red->out);
		ft_perror("shell", errno, nb);
		free(nb);
		return (1);
	}
	return (0);
}
