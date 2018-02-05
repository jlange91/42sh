/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 16:22:34 by stvalett          #+#    #+#             */
/*   Updated: 2018/01/30 16:22:36 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"

int		ft_exit_exec(t_cmd *cmd, int ret)
{
	DIR		*dir;

	dir = NULL;
	if (!cmd->av[1] && (dir = opendir(cmd->av[0])))
	{
		closedir(dir);
		return (42);
	}
	if (ret == 2)
	{
		ft_putstr_fd("shell: command not found: ", 2);
		ft_putendl_fd(cmd->av[0], 2);
	}
	else
		ft_perror("shell", ret, cmd->av[0]);
	return (1);
}
