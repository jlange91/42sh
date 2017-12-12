/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_push_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebrito <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 15:55:12 by adebrito          #+#    #+#             */
/*   Updated: 2017/05/22 15:55:13 by adebrito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_push_front(t_list **lst, t_list *new)
{
	t_list	*list;

	list = *lst;
	if (list)
	{
		new->next = list;
		list = new;
	}
	else
		*lst = ft_lstnew(new->content, new->content_size);
}
