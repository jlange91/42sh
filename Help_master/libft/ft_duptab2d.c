/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_duptab2d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebrito <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 15:53:01 by adebrito          #+#    #+#             */
/*   Updated: 2017/05/22 15:53:02 by adebrito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_duptab2d(char **tab)
{
	char	**new;
	int		i;

	if (!tab)
		return (0);
	i = 0;
	if (!(new = (char **)malloc(sizeof(char *) * (ft_strlen2d(tab) + 1))))
		return (0);
	while (tab[i])
	{
		new[i] = ft_strdup(tab[i]);
		i++;
	}
	new[i] = 0;
	return (new);
}
