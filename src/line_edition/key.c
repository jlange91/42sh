/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 19:23:04 by stvalett          #+#    #+#             */
/*   Updated: 2017/11/16 13:01:18 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"

/**************************************************************************************
 * FUNCTION FIND CURSOR
 * ALL VARIABLE :
 *
 * Explication : FIND CURSOR LOL;
 *
 * NO NORME
 * ***********************************************************************************/
static inline t_lineterm *find_cursor(t_lineterm *end)
{
	if (!end)
		return (NULL);
	while (end->s_pos == 0)
		end = end->prev;
	return (end);
}

static inline void 	ft_reset_var(t_termc *tsh, int flag)
{
	if (flag == 1)
	{
		if (ft_count_dlnk(tsh) == 0)
		{
			tsh->autoc->finish = 1;
			ft_init_simple_autocompl(tsh);
			tsh->line->last = 1;
		}
		ft_fill_history(tsh);
	}
	if (flag == 2  || flag == 3)
	{
		tsh->autoc->can_print = 0;
		tsh->count_tab = 0;
		tsh->auto_active = 0;
		tsh->multiauto_active = 0;
	}
	if (flag == 3)
	{
		ft_init_simple_autocompl(tsh);
		tsh->keyflag->backspace = 1;
	}
}
/************************************************************************************
 * FUNCTION SPLIT TWO PARTS: REMOVE CARACTERE WITH KEY BACKSPACE
 *
 * Explication : Delete one caractere, LOL EASY
 *
 * NO NORME
 * *********************************************************************************/
static inline int  ft_del_split(dlist **line, t_termc *tsh)
{
    t_lineterm  *tmp;

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

static inline int	ft_del_caractere(t_lineterm *end, t_termc *tsh)
{
	t_lineterm *tmp;

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

/*************************************************************************************
  FUNCTION ALL KEYS*/
/*ALL VARIABLE 	BEGIN WITH O ======> OPT-caractere
 * 		  		BEGIN WITH M ======> SHIFT-caractere
 * 		  		FLAG = 1 FOR NEXT = RIGHT
 * 		  		FLAG = 2 FOR PREV = LEFT
 * 		  		static int count    how time TAB, count == 0 go to TAB MENU or TAB = KEY RIGHT
 *
 * Explication : We fimnd cursor
 *
 * NO NORME
 ************************************************************************************/
int     ft_is_key(dlist *line, t_termc *tsh, long c)
{
    t_lineterm  *tmp;

    tmp = NULL;
	tmp = find_cursor(line->end);
	if (c == TAB && tsh->len_prompt >= (int)get_columns() - 3)
		return (1);
    if (c == TAB && !tsh->quotes)
        tsh->count_tab = 1;
    if (c == '\n' && !tsh->quotes)
		ft_reset_var(tsh, 2);
	if (c == BACKSPACE)
	{
		ft_reset_var(tsh, 3);
		if (!ft_del_caractere(tmp, tsh))
			return (0);
	}
    else if (c == UP && !tsh->quotes)
		ft_move_history(tsh, &tsh->history->current, 2);
	else if (c == DOWN && !tsh->quotes)
		ft_move_history(tsh, &tsh->history->current, 1);
	else if (!ft_other_key(tmp, tsh, c))
		return (0);
	return (1);
}
