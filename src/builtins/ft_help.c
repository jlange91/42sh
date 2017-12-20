/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 12:15:15 by adebrito          #+#    #+#             */
/*   Updated: 2017/12/20 17:06:44 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"

void	ft_help(t_cmd *cmd)
{
	char	**arg;
	pid_t	father;

	arg = NULL;
	father = fork();
	if (father == 0)
		execve("/tmp/./builtin_help", arg, cmd->env);
	else
		wait(0);
}
