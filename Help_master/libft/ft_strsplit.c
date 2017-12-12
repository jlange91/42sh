/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebrito <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 16:00:24 by adebrito          #+#    #+#             */
/*   Updated: 2017/05/22 16:00:25 by adebrito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbwords(char const *s, char c)
{
	size_t	nb;

	nb = 0;
	while (*s && s)
	{
		while (*s == c)
			s++;
		if (*s)
			nb++;
		while (*s && *s != c)
			s++;
	}
	return (nb);
}

char		**ft_strsplit(char const *s, char c)
{
	char		**str;
	const char	*tmp;
	size_t		i;

	if (!s)
		return (0);
	i = ft_nbwords(s, c);
	if (!(str = (char **)malloc(sizeof(char *) * (i + 1))))
		return (0);
	str[i] = NULL;
	i = 0;
	while (*s && s)
	{
		while (*s == c)
			s++;
		tmp = s;
		while (*s && *s != c)
			s++;
		if (tmp < s)
			str[i++] = ft_strsub(tmp, 0, (s - tmp));
	}
	return (str);
}
