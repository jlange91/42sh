/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirr_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 16:37:47 by jlange            #+#    #+#             */
/*   Updated: 2018/01/19 16:37:48 by jlange           ###   ########.fr       */
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

void		ft_redirr_type1(t_redir *red)
{
	dup2(red->out, (red->in == -1) ? 1 : red->in);
}

void		ft_redirr_type2(t_redir *red)
{
	dup2(red->out, (red->in == -1) ? 0 : red->in);
}
