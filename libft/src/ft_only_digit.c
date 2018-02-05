/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_only_digit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 18:46:36 by stvalett          #+#    #+#             */
/*   Updated: 2018/01/24 18:46:46 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_only_digit(char *av)
{
	int	i;

	i = 0;
	while (av[i] && av[i] == '-')
		i++;
	while (av[i] && ft_isdigit(av[i]))
		i++;
	if (i == ft_strlen(av))
		return (1);
	return (0);
}
