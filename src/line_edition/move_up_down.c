/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_up_down.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 18:58:20 by vmartins          #+#    #+#             */
/*   Updated: 2018/01/23 15:06:43 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"

void			ft_move_up_line(t_lineterm *end, t_termc *tsh)
{
	size_t		col;

	if (tsh->auto_active == 1 || tsh->multiauto_active == 1)
		return ;
	col = get_columns() - 1;
	if (end->prev)
	{
		while (end->prev && end->index != 0 && col > 0)
		{
			end->s_pos = 0;
			end->prev->s_pos = 1;
			end = end->prev;
			col--;
		}
		tsh->line->last = 0;
	}
}

void			ft_move_down_line(t_lineterm *end, t_termc *tsh)
{
	size_t		col;

	if (tsh->auto_active == 1 || tsh->multiauto_active == 1)
		return ;
	col = get_columns() - 1;
	if (end->next)
	{
		while (end->next && col > 0)
		{
			end->s_pos = 0;
			end->next->s_pos = 1;
			end = end->next;
			col--;
		}
	}
	if (!end->next)
		tsh->line->last = 1;
}

static	int		ft_move_history_split(t_history **current, int mode)
{
	int			ret;

	ret = 0;
	if ((*current)->next && mode == DOWN)
	{
		*current = (*current)->next;
		ret = 1;
	}
	if ((*current)->prev && mode == UP)
	{
		*current = (*current)->prev;
		ret = 1;
	}
	return (ret);
}

static	int		ft_passed_or_not(t_termc *tsh)
{
	t_lineterm	*begin;

	begin = tsh->line->begin;
	while (begin)
	{
		if (begin->under)
		{
			tsh->keyflag->underline = 1;
			return (0);
		}
		begin = begin->next;
	}
	return (1);
}

void			ft_move_history(t_termc *tsh, t_history **current, int mode)
{
	if (tsh->auto_active == 1 || tsh->multiauto_active == 1)
	{
		(mode == DOWN) ? ft_auto_down_up(NULL, tsh, 1) :
			ft_auto_down_up(NULL, tsh, 0);
		return ;
	}
	tsh->line->last = 1;
	if (!(*current) || !ft_passed_or_not(tsh) ||
			!ft_move_history_split(current, mode))
		return ;
	if (ft_count_dlnk(tsh, 0) >= 1)
		ft_clean_line(tsh);
	ft_cpy_to_line((*current)->data, tsh);
	tsh->line->last = 1;
}
