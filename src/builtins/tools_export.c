/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 14:25:57 by adebrito          #+#    #+#             */
/*   Updated: 2018/01/04 16:07:37 by adebrito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"

void	ft_display_export(char **var)
{
	int	i;

	i = -1;
	while (var[++i])
	{
		ft_putstr("export ");
		ft_putendl(var[i]);
	}
}

int		only_p(t_cmd *cmd)
{
	int i;

	i = 0;
	while (cmd->av[++i])
	{
		if (ft_strcmp(cmd->av[i], "-p"))
			return (0);
	}
	ft_display_export(cmd->var);
	return (1);
}

int		check_pattern(char *str)
{
	int		i;
	char	**tmp;

	i = -1;
	tmp = ft_strsplit(str, '=');
	if (tmp[0])
	{
		while (tmp[0][++i])
		{
			if (ft_isalpha(tmp[0][i]) == 0)
			{
				ft_free_tab(tmp);
				return (0);
			}
		}
		ft_free_tab(tmp);
	}
	return (1);
}
