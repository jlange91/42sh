/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabcreate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 16:01:22 by vmartins          #+#    #+#             */
/*   Updated: 2017/05/22 16:01:23 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tabcreate(char *content)
{
	char	**new;
	int		i;

	i = 0;
	if (!(new = (char **)malloc(sizeof(char *) * 2)))
		return (NULL);
	new[i] = content;
	new[++i] = NULL;
	return (new);
}
