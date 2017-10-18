/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rot13.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 18:17:36 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/31 15:26:18 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_rot13(char *str, int n)
{
	int i;

	if (!str || (n < 1 || n > 25))
		return ;
	i = 0;
	while (str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] = ((((str[i] - 'a') + n) % 26) + 'a');
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] = ((((str[i] - 'A') + n) % 26) + 'A');
		i++;
	}
	ft_putstr(str);
}
