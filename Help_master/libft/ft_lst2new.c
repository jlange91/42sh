/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst2new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 15:54:49 by vmartins          #+#    #+#             */
/*   Updated: 2017/05/22 15:54:50 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_history	*ft_listenew(char *content)
{
	t_history	*new;

	if (!(new = (t_history *)malloc(sizeof(*new))))
		return (0);
	if (content == NULL)
		new->content = "";
	else
		new->content = ft_strdup(content);
	new->previous = NULL;
	new->next = NULL;
	return (new);
}
