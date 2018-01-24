/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 14:41:21 by jlange            #+#    #+#             */
/*   Updated: 2018/01/23 14:41:23 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"

void	check_env_export(char *tmp, char *str)
{
	if (ft_getenv(tmp, ft_var_env(NULL)) != NULL)
		basic_replace(tmp, str, ft_var_env(NULL));
	if (ft_getenv(tmp, ft_var_var(NULL)) != NULL)
		basic_replace(tmp, str, ft_var_var(NULL));
}

int		place_me(t_cmd *cmd)
{
	int		i;
	int		save;

	i = 1;
	save = 0;
	while (cmd->av[++i])
	{
		if (ft_strcmp(cmd->av[i], "-p"))
		{
			if (save == 0)
				save = i - 1;
		}
	}
	return (save);
}
