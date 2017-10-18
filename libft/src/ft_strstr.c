/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 17:06:03 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/31 15:33:12 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	char	*tmp1;
	char	*tmp2;

	if (!*little)
		return ((char *)big);
	while (*big)
	{
		tmp1 = (char *)big;
		tmp2 = (char *)little;
		while (*tmp1 && *tmp2 && *tmp1 == *tmp2)
		{
			tmp1++;
			tmp2++;
		}
		if (*tmp2 == '\0')
			return ((char *)big);
		big++;
	}
	return (0);
}
