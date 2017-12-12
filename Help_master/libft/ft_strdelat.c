/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdelat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebrito <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 15:59:06 by adebrito          #+#    #+#             */
/*   Updated: 2017/05/22 15:59:07 by adebrito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdelat(char *str, size_t position)
{
	size_t	i;
	size_t	j;
	char	*new;

	if (!str)
		return (0);
	i = 0;
	j = 0;
	if (!(new = (char *)malloc(sizeof(char) * ft_strlen(str))))
		return (0);
	while (str[j])
	{
		if (j == position)
			j++;
		new[i] = str[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
}
