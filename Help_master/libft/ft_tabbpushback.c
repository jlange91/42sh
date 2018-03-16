/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabbpushback.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 16:01:18 by vmartins          #+#    #+#             */
/*   Updated: 2017/05/22 16:01:18 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	***ft_tabbpushback(char ***tab, char **content)
{
	char	***new;
	int		i;
	int		size;

	i = -1;
	if (tab == NULL)
		return ((new = ft_tabbcreate(content)));
	size = (ft_tabblen(tab) + 1);
	if (!(new = (char ***)malloc(sizeof(char **) * size + 1)))
		return (NULL);
	while (tab[++i])
		new[i] = ft_tabdup(tab[i]);
	new[i] = ft_tabdup(content);
	new[++i] = NULL;
	ft_freetabb(tab, ft_tabblen(tab));
	return (new);
}
