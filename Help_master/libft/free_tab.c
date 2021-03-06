/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 14:32:17 by vmartins          #+#    #+#             */
/*   Updated: 2017/11/22 13:17:19 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_tab(void **tab, int len)
{
	int i;

	i = -1;
	while (++i < len)
		ft_memdel(&tab[i]);
	free(tab);
	tab = NULL;
}
