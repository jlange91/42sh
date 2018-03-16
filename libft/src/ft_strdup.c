/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 12:38:36 by vmartins          #+#    #+#             */
/*   Updated: 2018/01/24 18:48:51 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;

	if ((str = (char *)malloc(sizeof(*str) * (ft_strlen(s1) + 1))) == NULL)
		return (NULL);
	ft_strcpy(str, s1);
	return (str);
}
