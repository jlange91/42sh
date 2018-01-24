/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_selection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 18:57:13 by stvalett          #+#    #+#             */
/*   Updated: 2018/01/22 18:58:04 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"

void	ft_move_right(t_lineterm *end, t_termc *tsh)
{
	if (tsh->auto_active || tsh->multiauto_active)
	{
		if (tsh->console->total_line > 1)
			return ;
		ft_automove(end, tsh, 1);
		return ;
	}
	tsh->auto_active = 0;
	tsh->multiauto_active = 0;
	if (end && end->next)
	{
		if (tsh->keyflag->underline && end->next->under != 1)
			end->next->under = 1;
		else if (tsh->keyflag->underline && end->next->under == 1)
			end->next->under = 0;
		end->s_pos = 0;
		end->next->s_pos = 1;
		if (!end->next->next)
			tsh->line->last = 1;
		else
			tsh->line->lnk_before = 1;
	}
}

void	ft_move_left(t_lineterm *end, t_termc *tsh)
{
	if (tsh->auto_active || tsh->multiauto_active)
	{
		if (tsh->console->total_line > 1)
			return ;
		ft_automove(end, tsh, 0);
		return ;
	}
	tsh->auto_active = 0;
	tsh->multiauto_active = 0;
	if (end->prev && end->index != 0)
	{
		if (tsh->keyflag->underline && end->under != 1)
			end->under = 1;
		else if (tsh->keyflag->underline && end->under == 1)
			end->under = 0;
		end->s_pos = 0;
		end->prev->s_pos = 1;
		tsh->line->last = 0;
	}
}

void	ft_move_mleft(t_lineterm *end, t_termc *tsh)
{
	if (tsh->auto_active || tsh->multiauto_active)
		return ;
	tsh->keyflag->underline = 1;
	ft_move_left(end, tsh);
}

void	ft_move_mright(t_lineterm *end, t_termc *tsh)
{
	if (tsh->auto_active || tsh->multiauto_active)
		return ;
	tsh->keyflag->underline = 1;
	ft_move_right(end, tsh);
}
