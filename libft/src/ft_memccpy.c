/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 19:54:09 by vmartins          #+#    #+#             */
/*   Updated: 2017/03/31 15:48:06 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char		*tmp_d;
	const char	*tmp_s;
	int			i;

	i = 0;
	tmp_d = dst;
	tmp_s = src;
	while (i < (int)n)
	{
		tmp_d[i] = tmp_s[i];
		if (tmp_s[i] == (char)c)
			return ((void *)&tmp_d[i + 1]);
		i++;
	}
	return (0);
}
