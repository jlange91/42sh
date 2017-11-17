/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_useless_norme.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 18:06:04 by jlange            #+#    #+#             */
/*   Updated: 2017/11/16 14:50:41 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"

char	*ft_useless_norme(void)
{
	char *str;

	str = "Input/output error. Some physical input or output error occurred.";
	return (ft_strdup(str));
}
