/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 19:45:54 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/31 15:26:31 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_sort_int_tab(int *tab, int n)
{
	int i;
	int	j;
	int	tmp;

	if (n <= 0 || !tab)
		return ;
	i = 0;
	tmp = 0;
	j = 1;
	while (j)
	{
		j = 0;
		while (i < n)
		{
			if (tab[i] > tab[i + 1])
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				j = 1;
			}
			i++;
		}
		i = 0;
	}
}
