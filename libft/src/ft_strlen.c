/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 12:23:57 by stvalett          #+#    #+#             */
/*   Updated: 2017/10/02 19:05:52 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
    if (!s)
    {
        return (-1);
    }
	while (s[i])
		i++;
	return (i);
}
