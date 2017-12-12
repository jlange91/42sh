/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebrito <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 15:56:40 by adebrito          #+#    #+#             */
/*   Updated: 2017/05/22 15:56:41 by adebrito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*str_dest;
	char	*str_src;
	size_t	i;

	i = 0;
	str_dest = (char*)dest;
	str_src = (char*)src;
	if (src < dest)
	{
		while (n)
		{
			n--;
			str_dest[n] = str_src[n];
		}
	}
	else
	{
		while (i < n)
		{
			str_dest[i] = str_src[i];
			i++;
		}
	}
	return (dest);
}
