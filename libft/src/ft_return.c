/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_return.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 18:47:22 by vmartins          #+#    #+#             */
/*   Updated: 2018/01/24 18:47:45 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_returnfree(char *str, int ret, char c)
{
	if (c == 'f')
	{
		if (str)
			free(str);
	}
	return (ret);
}
