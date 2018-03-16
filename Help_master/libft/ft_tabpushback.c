/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabpushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 16:01:42 by vmartins          #+#    #+#             */
/*   Updated: 2017/05/22 16:01:43 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tabpushback(char **tab, char *content)
{
	char	**new;
	int		i;
	int		size;

	i = -1;
	if (tab == NULL)
		return ((new = ft_tabcreate(content)));
	size = (ft_tablen(tab) + 1);
	if (!(new = (char **)malloc(sizeof(char *) * size + 1)))
		return (NULL);
	while (tab[++i])
		new[i] = ft_strdup(tab[i]);
	new[i] = ft_strdup(content);
	new[++i] = NULL;
	ft_freetab(&tab);
	return (new);
}
