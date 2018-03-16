/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 19:23:04 by vmartins          #+#    #+#             */
/*   Updated: 2018/01/23 15:31:09 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"
#include "../../inc/globbing.h"

void					ft_ctr_d(t_termc *tsh)
{
	t_lineterm			*end;
	int					count;

	if (tsh->auto_active || tsh->multiauto_active)
		return ;
	count = (tsh->hdoc || tsh->quotes) ? ft_count_dlnk(tsh, 1) :
	ft_count_dlnk(tsh, 0);
	if (count >= 1)
	{
		end = find_cursor(tsh->line->end, 0);
		if (end && end->next)
		{
			end->next->under = 1;
			ft_cut_line(end, tsh);
		}
	}
	else if (tsh->hdoc || tsh->quotes)
		return ;
	else
	{
		ft_putchar('\n');
		ft_end_term(tsh);
		exit(1);
	}
}

static	inline	void	ft_reset_var(t_termc *tsh, int flag)
{
	if (flag == 1)
	{
		if (ft_count_dlnk(tsh, 0) == 0)
		{
			ft_init_simple_autocompl(tsh, 0, NULL);
			tsh->autoc->finish = 1;
			tsh->line->last = 1;
		}
		ft_fill_history(tsh);
	}
	if (flag == 2 || flag == 3)
	{
		tsh->autoc->can_print = 0;
		tsh->keyflag->k_tab = 0;
		tsh->auto_active = 0;
		tsh->multiauto_active = 0;
	}
	if (flag == 3)
		ft_init_simple_autocompl(tsh, 0, NULL);
}

static	inline	int		ft_del_split(t_dlst **line, t_termc *tsh)
{
	t_lineterm			*tmp;

	tmp = (*line)->end;
	if (!tmp)
		return (0);
	(*line)->end = tmp->prev;
	if ((*line)->end)
		(*line)->end->next = NULL;
	else
	{
		(*line)->begin = NULL;
		return (0);
	}
	(*line)->end->s_pos = 1;
	tsh->line->last = 1;
	return (1);
}

static	inline	int		ft_del_caractere(t_lineterm *end, t_termc *tsh)
{
	t_lineterm			*tmp;

	tmp = end;
	if (!tmp || tmp->index == 0)
	{
		ft_reset_var(tsh, 1);
		return (0);
	}
	else if (!tmp->next && tmp->index != 0)
	{
		if (!ft_del_split(&(tsh)->line, tsh))
			return (0);
		if (tmp->prev->index == 0)
			ft_reset_var(tsh, 1);
	}
	else if (tmp->prev && tmp->index != 0)
	{
		end->prev->next = tmp->next;
		end->next->prev = tmp->prev;
		end->prev->s_pos = 1;
		tsh->line->last = 0;
	}
	free(tmp);
	return (1);
}

int						ft_action_key(t_dlst *line, t_termc *tsh, long c)
{
	t_lineterm			*tmp;

	tmp = NULL;
	tmp = find_cursor(line->end, 0);
	if (c == ' ')
		ft_replace_exp_hist(tsh);
	if (c == TAB && !tsh->quotes && !tsh->hdoc)
		tsh->keyflag->k_tab = 1;
	if (c == '\n' && !tsh->quotes && !tsh->hdoc)
		ft_reset_var(tsh, 2);
	if (c == BACKSPACE)
	{
		ft_reset_var(tsh, 3);
		if (!ft_del_caractere(tmp, tsh))
			return (0);
	}
	else if (c == UP)
		ft_move_history(tsh, &tsh->histmp->current, UP);
	else if (c == DOWN)
		ft_move_history(tsh, &tsh->histmp->current, DOWN);
	else if (!ft_other_key(tmp, tsh, c))
		return (0);
	return (1);
}
