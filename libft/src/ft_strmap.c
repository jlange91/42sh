/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 05:02:23 by vmartins          #+#    #+#             */
/*   Updated: 2017/03/31 15:30:27 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	int		j;
	char	*ptr;

	if (!s || !(*f))
		return (NULL);
	j = ft_strlen(s);
	if ((ptr = (char *)malloc(sizeof(*ptr) * j + 1)) == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ptr[i] = f(s[i]);
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
