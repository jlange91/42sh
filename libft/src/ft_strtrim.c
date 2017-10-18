/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 18:35:08 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/31 15:52:07 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strtrim(char const *s)
{
	char		*str;
	char const	*start;
	char const	*end;

    start = NULL;
	if (!s)
		return (NULL);
	while (*s)
	{
		if (!(*s == ' ' || *s == '\t' || *s == '\n'))
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
	s = start;
	while (s <= end)
		*str++ = *s++;
	*str = '\0';
	return (str - (end - start + 1));
}
