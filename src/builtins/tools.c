/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 14:41:21 by jlange            #+#    #+#             */
/*   Updated: 2018/01/30 15:44:09 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"

void	check_env_export(char *tmp, char *str, int index)
{
	char	*tstr;

	tstr = NULL;
	if (index == 0)
	{
		tstr = str;
		if (!ft_strchr(str, '='))
			str = ft_strjoin(str, "=");
		if (ft_getenv(tmp, ft_var_env(NULL)) != NULL)
			basic_replace(tmp, str, ft_var_env(NULL));
		if (ft_getenv(tmp, ft_var_var(NULL)) != NULL)
			basic_replace(tmp, str, ft_var_var(NULL));
		if (ft_strcmp(tstr, str))
			free(str);
	}
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
