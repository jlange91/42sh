/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 12:02:40 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/31 15:32:38 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen(s) - 1;
	if (!c)
		return ((char *)s + i + 1);
	while (s[i] != 0 && s[i] != (char)c)
		i--;
	if (s[i] == (char)c)
		return ((char *)s + i);
	else
		return (0);
}
