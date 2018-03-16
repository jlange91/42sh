/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 16:00:49 by vmartins          #+#    #+#             */
/*   Updated: 2017/05/22 16:00:50 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	i;
	char	*new;
	size_t	index_debut;
	size_t	index_fin;

	if (!s)
		return (0);
	if (ft_strlen(s) == 0)
		return ((char*)malloc(sizeof(*new) * (0)));
	i = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i++;
	if (s[i] == '\0')
		return ((ft_strsub(s, 0, 0)));
	index_debut = i;
	while (s[i])
		i++;
	while (s[i] == ' ' || s[i] == '\0' || s[i] == '\t' || s[i] == '\n')
		i--;
	index_fin = i;
	new = ft_strsub(s, (index_debut), (index_fin - index_debut + 1));
	return (new);
}
