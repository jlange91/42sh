/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_back.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 21:36:37 by vmartins          #+#    #+#             */
/*   Updated: 2017/03/31 15:24:16 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_push_back(t_list **alst, t_list *elem)
{
	t_list	*tmp;

	tmp = *alst;
	if (!*alst || !elem)
		return ;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = elem;
	elem->next = NULL;
}
