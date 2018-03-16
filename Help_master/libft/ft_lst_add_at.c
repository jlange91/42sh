/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_add_at.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 15:55:01 by vmartins          #+#    #+#             */
/*   Updated: 2017/06/06 10:58:03 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_add_at(t_list **lst, t_list *new, int position)
{
	int		i;
	t_list	*list;

	if (!(*lst))
		*lst = new;
	else
	{
		i = 0;
		list = *lst;
		while (list->next && i < position)
		{
			list = list->next;
			i++;
		}
		list->next = new;
	}
}
