/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 08:27:44 by vmartins          #+#    #+#             */
/*   Updated: 2017/03/31 15:21:01 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	ft_negative(int n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

static int	ft_nbrlen(int n)
{
	int count;

	if (!n)
		return (1);
	count = 0;
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static char	*new_str(int neg, int len)
{
	char	*str;

	if ((str = (char *)malloc(sizeof(*str) * len + 1)) != NULL)
	{
		if (neg > 0)
			str[0] = '-';
		str[len] = '\0';
		return (str);
	}
	return (NULL);
}

char		*ft_itoa(int n)
{
	int				i;
	unsigned int	j;
	int				len;
	int				neg;
	char			*str;

	str = NULL;
	neg = 0;
	if (n < 0)
		neg = 1;
	len = ft_nbrlen(n) + neg;
	j = ft_negative(n);
	if ((str = new_str(neg, len)) != NULL)
	{
		i = len - 1;
		while (i >= neg)
		{
			str[i] = (char)(j % 10) + '0';
			j /= 10;
			i--;
		}
	}
	return (str);
}
