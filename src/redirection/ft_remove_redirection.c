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

void		ft_test_fd(void)
{
	int				i;
	int				max;
	struct stat		buf;
	struct rlimit	limit;

	max = (getrlimit(RLIMIT_NOFILE, &limit) == 0) ? limit.rlim_cur : 1024;
	i = 3;
	while (i < max)
	{
		if (!fstat(i, &buf))
			close(i);
		i++;
	}
}

void		ft_remove_redirection(void)
{
	dup2(ft_backup_stdin(0), 0);
	close(ft_backup_stdin(0));
	dup2(ft_backup_stdout(0), 1);
	close(ft_backup_stdout(0));
	dup2(ft_backup_stderr(0), 2);
	close(ft_backup_stderr(0));
	ft_test_fd();
}
