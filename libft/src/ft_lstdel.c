/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 13:43:13 by vmartins          #+#    #+#             */
/*   Updated: 2017/03/31 15:21:28 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	if (!alst || !(*del))
		return ;
	else
	{
		while (*alst)
		{
			(*del)((*alst)->content, (*alst)->content_size);
			if ((*alst)->next == NULL)
			{
				free(*alst);
				*alst = NULL;
			}
			else
				*alst = (*alst)->next;
		}
	}
}
