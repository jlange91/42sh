/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 12:15:15 by adebrito          #+#    #+#             */
/*   Updated: 2018/01/03 13:01:16 by adebrito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"

void	ft_help(void)
{
	char	**arg;
	pid_t	father;

	arg = NULL;
	father = fork();
	if (father == 0)
		execve("/tmp/./builtin_help", arg, ft_var_env(NULL));
	else
		wait(0);
}
