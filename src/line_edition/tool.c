/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <vmartins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 19:24:14 by vmartins          #+#    #+#             */
/*   Updated: 2018/01/23 15:31:02 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/line_edition.h"

static	void	ft_split_clean(t_termc *tsh, t_lineterm *end, int mode)
{
	if (mode == 1)
	{
		tsh->line->end = end->prev;
		tsh->line->end->next = NULL;
	}
	else if (mode == 2)
	{
		tsh->line->begin = end->next;
		tsh->line->begin->prev = NULL;
	}
	else if (mode == 3)
	{
		end->prev->next = end->next;
		end->next->prev = end->prev;
	}
}

void			ft_clean_line(t_termc *tsh)
{
	t_lineterm	*end;
	t_lineterm	*del;

	end = tsh->line->end;
	while (end)
	{
		if (end->index == 0)
			break ;
		del = end;
		if (end->next == NULL)
			ft_split_clean(tsh, end, 1);
		else if (end->prev == NULL)
			ft_split_clean(tsh, end, 2);
		else
			ft_split_clean(tsh, end, 3);
		end = end->prev;
		free(del);
	}
}

t_lineterm		*ft_ps1(t_lineterm *tmp)
{
	int			i;

	i = 0;
	while (tmp)
	{
		if (i > 7)
			break ;
		i++;
		tmp = tmp->next;
	}
	return (tmp);
}
