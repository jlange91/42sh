/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebrito <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 17:51:12 by adebrito          #+#    #+#             */
/*   Updated: 2018/01/23 15:46:29 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"

char	*get_env(char *elem_tab)
{
	int		i;
	char	*result;

	i = 0;
	result = NULL;
	while (elem_tab[i] != '=')
		i++;
	result = ft_strsub(elem_tab, 0, i);
	return (result);
}

void	update_local(int i, int j)
{
	char	**tenv;
	char	**t_local;
	char	*tmp1;
	char	*tmp2;

	tenv = ft_var_env(NULL);
	t_local = ft_var_local(NULL);
	while (tenv[++i])
	{
		tmp1 = get_env(tenv[i]);
		while (t_local[++j])
		{
			tmp2 = get_env(t_local[j]);
			if (!ft_strcmp(tmp1, tmp2))
			{
				free(t_local[j]);
				t_local[j] = ft_strdup(tenv[i]);
			}
			free(tmp2);
		}
		free(tmp1);
		j = -1;
	}
}

void	update_export(int i, int j)
{
	char	**tenv;
	char	**texport;
	char	*tmp1;
	char	*tmp2;

	tenv = ft_var_env(NULL);
	texport = ft_var_var(NULL);
	while (tenv[++i])
	{
		tmp1 = get_env(tenv[i]);
		while (texport[++j])
		{
			tmp2 = get_env(texport[j]);
			if (!ft_strcmp(tmp1, tmp2))
			{
				free(texport[j]);
				texport[j] = ft_strdup(tenv[i]);
			}
			free(tmp2);
		}
		free(tmp1);
		j = -1;
	}
}
