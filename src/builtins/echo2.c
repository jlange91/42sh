/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 18:25:33 by jlange            #+#    #+#             */
/*   Updated: 2017/11/03 18:34:13 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"

static int		ft_is_hexa(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else if (c >= 'a' && c <= 'f')
		return (1);
	else if (c >= 'A' && c <= 'F')
		return (1);
	else
		return (0);
}

static int		ft_is_octal(char c)
{
	return (c >= '0' && c <= '7') ? 1 : 0;
}

int				display_octal(char *str)
{
	int i;
	int nb;
	int mult;
	int save;

	i = 0;
	nb = 0;
	mult = 1;
	while (str[i] && i < 3 && ft_is_octal(str[i]))
		i++;
	if (i == 0)
		return (0);
	save = i;
	while (--i >= 0)
	{
		nb += (str[i] >= '0' && str[i] <= '7') ? (str[i] - 48) * mult : 0;
		mult *= 8;
	}
	ft_putchar(nb);
	return (save);
}

int				display_hexa(char *str)
{
	int i;
	int nb;
	int mult;
	int save;

	i = 0;
	nb = 0;
	mult = 1;
	while (str[i] && i < 2 && ft_is_hexa(str[i]))
		i++;
	if (i == 0)
		return (0);
	save = i;
	while (--i >= 0)
	{
		nb += (str[i] >= '0' && str[i] <= '9') ? (str[i] - 48) * mult : 0;
		nb += (str[i] >= 'a' && str[i] <= 'f') ? (str[i] - 87) * mult : 0;
		nb += (str[i] >= 'A' && str[i] <= 'F') ? (str[i] - 55) * mult : 0;
		mult *= 16;
	}
	ft_putchar(nb);
	return (save);
}
