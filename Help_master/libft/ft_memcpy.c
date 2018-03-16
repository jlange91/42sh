/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 15:56:13 by vmartins          #+#    #+#             */
/*   Updated: 2017/05/22 15:56:15 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*str_dest;
	char	*str_src;

	str_dest = (char*)dest;
	str_src = (char*)src;
	while (n != 0)
	{
		n--;
		str_dest[n] = str_src[n];
	}
	return (dest);
}
