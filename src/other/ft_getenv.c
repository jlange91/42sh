/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 18:42:39 by jlange            #+#    #+#             */
/*   Updated: 2017/11/03 18:46:46 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"

char	*ft_getenv(const char *name, char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strjoin(name, "=");
	while (env[i] != NULL && ft_strncmp(tmp, env[i], ft_strlen(tmp)))
		i++;
	free(tmp);
	return (env[i] == NULL) ? NULL : env[i];
}
