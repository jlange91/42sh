/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 18:46:59 by vmartins          #+#    #+#             */
/*   Updated: 2018/01/24 18:47:12 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_remove_char(char *str, char c)
{
	char	*new;
	int		i;
	int		j;

	new = NULL;
	if ((new = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1))) == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	ft_strdel(&str);
	return (new);
}
