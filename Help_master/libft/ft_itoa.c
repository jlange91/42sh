/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 15:54:35 by vmartins          #+#    #+#             */
/*   Updated: 2017/05/22 15:54:36 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	nbcase(int n)
{
	size_t		i;

	i = 1;
	if (n == 0)
		return (2);
	if (n < 0)
		n *= -1;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char		*itoa_min(void)
{
	char	*nb;
	size_t	i;
	size_t	n;

	i = 12;
	n = 2147483648;
	if (!(nb = (char *)malloc(sizeof(*nb) * i)))
		return (0);
	i--;
	nb[i] = '\0';
	while (i)
	{
		i--;
		nb[i] = (n % 10) + 48;
		n /= 10;
	}
	nb[0] = '-';
	return (nb);
}

char			*ft_itoa(int n)
{
	size_t	i;
	size_t	sign;
	char	*nb;

	sign = 0;
	i = nbcase(n);
	if (n == -2147483648)
		return (itoa_min());
	if (n < 0)
	{
		i += 1;
		sign = 1;
		n *= -1;
	}
	if (!(nb = (char *)malloc(sizeof(*nb) * i)))
		return (0);
	nb[--i] = '\0';
	while (i)
	{
		nb[--i] = (n % 10) + 48;
		n /= 10;
	}
	if (sign == 1)
		nb[0] = '-';
	return (nb);
}
