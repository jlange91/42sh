/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_useless_path.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 18:42:48 by jlange            #+#    #+#             */
/*   Updated: 2017/11/03 18:47:49 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"

static inline char	*add_path(char *str1, char *str2)
{
	char *ret;
	char *tmp;

	ret = ft_strdup("/");
	tmp = ret;
	ret = ft_strjoin(ret, str2);
	free(tmp);
	if (str1)
	{
		tmp = ret;
		ret = ft_strjoin(str1, ret);
		free(tmp);
		free(str1);
	}
	return (ret);
}

static inline char	*split_to_path(char **split)
{
	char	*ret;
	int		i;

	i = 0;
	ret = NULL;
	while (split[i])
	{
		if (ft_strcmp(split[i], "."))
			ret = add_path(ret, split[i]);
		++i;
	}
	return (ret == NULL) ? (ft_strdup("/")) : (ret);
}

char				*ft_remove_useless_path(char *str)
{
	char	*ret;
	char	**split;
	int		i;

	i = 0;
	split = ft_strsplit(str, '/');
	while (split[i])
	{
		if (!ft_strcmp(split[i], ".."))
		{
			free(split[i]);
			split[i] = ft_strdup(".");
			while (!ft_strcmp(split[i], ".") && i > 0)
				i--;
			free(split[i]);
			split[i] = ft_strdup(".");
		}
		else
			++i;
	}
	ret = split_to_path(split);
	free_tab_2d(split);
	return (ret);
}
