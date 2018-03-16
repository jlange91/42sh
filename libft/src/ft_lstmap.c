/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 15:01:04 by vmartins          #+#    #+#             */
/*   Updated: 2017/03/31 15:22:13 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;

	if (!lst)
		return (NULL);
	if ((new = (t_list *)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	new = f(lst);
	new->next = ft_lstmap(lst->next, f);
	return (new);
}
