/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 19:08:26 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/31 15:48:26 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*tmp;
	int				i;

	i = 0;
	tmp = (unsigned char *)s;
	if (n == 0)
		return ;
	while (i < (int)n)
	{
		tmp[i] = '\0';
		i++;
	}
}
