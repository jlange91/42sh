/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 12:15:15 by adebrito          #+#    #+#             */
/*   Updated: 2018/01/24 15:53:04 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"

void	ft_help(void)
{
	char		**arg;
	pid_t		father;
	struct stat	info;

	ft_memset(&info, 0, sizeof(info));
	if ((stat("/tmp/builtin_help", &info)) < 0)
		return ;
	signal(SIGINT, SIG_IGN);
	arg = NULL;
	father = fork();
	if (father == 0)
		execve("/tmp/./builtin_help", arg, ft_var_var(NULL));
	else
		wait(0);
}
