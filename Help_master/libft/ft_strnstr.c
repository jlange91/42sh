/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 16:00:14 by vmartins          #+#    #+#             */
/*   Updated: 2017/05/22 16:00:15 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *search, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (ft_strcmp(search, "") == 0)
		return ((char*)str);
	while (str[i] && i < n)
	{
		if (str[i] == search[j])
		{
			while (str[i + j] == search[j] && search[j] && (i + j) < n)
				j++;
			if (search[j] == '\0')
				return ((char*)str + i);
			j = 0;
		}
		i++;
	}
	return (0);
}
