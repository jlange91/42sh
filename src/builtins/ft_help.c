/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 12:15:15 by vmartins          #+#    #+#             */
/*   Updated: 2018/02/13 11:36:57 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"
#include "../../inc/line_edition.h"

void	ft_help(void)
{
	char		**arg;
	pid_t		father;
	struct stat	info;

	ft_memset(&info, 0, sizeof(info));
	if ((stat("/tmp/builtin_help", &info)) < 0)
	{
		ft_perror("shell", errno, NULL);
		return ;
	}
	signal(SIGINT, SIG_IGN);
	arg = NULL;
	father = fork();
	if (father == 0)
		execve("/tmp/./builtin_help", arg, ft_var_var(NULL));
	else
		wait(0);
	signal(SIGINT, ft_handle_signal);
}
