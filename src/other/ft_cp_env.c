/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cp_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 18:42:12 by jlange            #+#    #+#             */
/*   Updated: 2017/11/03 18:42:12 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"

char	**ft_cp_env(char **env)
{
	char	**c_env;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (env[len] != NULL)
		len++;
	if (!(c_env = (char**)malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	while (i < len)
	{
		c_env[i] = ft_strdup(env[i]);
		i++;
	}
	c_env[i] = NULL;
	return (c_env);
}
