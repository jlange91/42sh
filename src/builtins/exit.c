/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 12:58:14 by vmartins          #+#    #+#             */
/*   Updated: 2018/02/27 11:21:52 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/line_edition.h"

int		argument_is_ok(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		++i;
	}
	return (1);
}

void	ft_exit(t_cmd *cmd)
{
	unsigned char	nb;
	t_termc			*tsh;

	if (cmd->ac > 2)
	{
		ft_putstr_fd("Too many arguments\n", 2);
		ft_singleton(1, 1);
		return ;
	}
	else if (cmd->ac == 2 && !argument_is_ok(cmd->av[1]))
	{
		ft_putstr("Only numeric characters\n");
		ft_singleton(1, 1);
		return ;
	}
	nb = (cmd->ac == 1) ? 0 : ft_atoi(cmd->av[1]);
	ft_putstr("exit\n");
	tsh = ft_ret_tsh(NULL);
	ft_add_file_history(tsh);
	exit(nb);
}
