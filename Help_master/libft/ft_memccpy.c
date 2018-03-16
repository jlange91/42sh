/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 15:55:57 by vmartins          #+#    #+#             */
/*   Updated: 2017/05/22 15:55:58 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	char	*str_dest;
	char	*str_src;
	size_t	i;

	str_dest = (char*)dest;
	str_src = (char*)src;
	i = 0;
	while (i < n)
	{
		str_dest[i] = str_src[i];
		if (str_src[i] == c)
			return ((char*)dest + ++i);
		i++;
	}
	return (0);
}
