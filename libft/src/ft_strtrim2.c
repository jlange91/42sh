/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 10:01:49 by vmartins          #+#    #+#             */
/*   Updated: 2017/03/31 15:34:07 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strtrim2(char const *s, char c1, char c2)
{
	char		*str;
	char const	*start;
	char const	*end;

	start = NULL;
	if (!s)
		return ((char *)s);
	while (*s)
	{
		if (!(*s == c1 || *s == c2))
		{
			start = (start == NULL) ? s : start;
			end = s;
		}
		s++;
	}
	if (start == NULL)
		return (ft_strnew(1));
	if ((str = (char *)malloc(sizeof(*str) * (end - start) + 2)) == NULL)
		return (NULL);
	s = (char *)start;
	while (s <= end)
		*str++ = *s++;
	*str = '\0';
	return (str - (end - start + 1));
}
