/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 16:38:04 by jlange            #+#    #+#             */
/*   Updated: 2018/01/19 16:38:10 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"

void		ft_remove_redirection(void)
{
	dup2(ft_backup_stdin(0), 0);
	close(ft_backup_stdin(0));
	dup2(ft_backup_stdout(0), 1);
	close(ft_backup_stdout(0));
	dup2(ft_backup_stderr(0), 2);
	close(ft_backup_stderr(0));
}
