/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freetab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 15:54:02 by vmartins          #+#    #+#             */
/*   Updated: 2017/05/22 15:54:03 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_freetab(char ***tab)
{
	size_t	i;
	char	*str;

	i = 0;
	while ((str = (*tab)[i]))
	{
		ft_strdel(&str);
		i++;
	}
	ft_strdel(&(*tab)[i]);
	free(*tab);
	*tab = NULL;
}
