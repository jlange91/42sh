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

/************************************************************************************
 * FUNCTION SPLIT TWO PARTS: REMOVE CARACTERE WITH KEY BACKSPACE
 *
 * Explication : Delete one caractere, LOL EASY
 *
 * NO NORME
 * *********************************************************************************/
static inline int  ft_del_split(dlist **line, t_termc *shell)
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
	shell->line->last = 1;
	return (1);
}

static inline int	ft_del_caractere(t_lineterm *end, t_termc *shell, char **env)
{
	t_lineterm *tmp;

	tmp = end;
	if (!tmp || tmp->index == 0)
	{
        if (ft_count_dlnk(shell) == 0)
		{
        	shell->autocompl->finish = 1;
            ft_init_simple_autocompl(shell, env);
		    shell->line->last = 1;
		}
		ft_fill_history(shell);
		return (0);
	}
	else if (!tmp->next && tmp->index != 0)
	{
		if (!ft_del_split(&(shell)->line, shell))
			return (0);
	}
	else if (tmp->prev && tmp->index != 0)
	{
		end->prev->next = tmp->next;
		end->next->prev = tmp->prev;
		end->prev->s_pos = 1;
        shell->line->last = 0;
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
 * Explication : We find cursor 
 *
 * NO NORME
 ************************************************************************************/
int     ft_is_key(dlist *line, t_termc *shell, long c, char **env)
{
    t_lineterm  *tmp;

    tmp = NULL;
	tmp = find_cursor(line->end);
	if (c == TAB && shell->len_prompt >= (int)get_columns() - 3)
		return (1);
    if (c == TAB && !shell->quotes)
        shell->count_tab = 1;
    if (c == '\n' && !shell->quotes)
	{
		shell->autocompl->can_print = 0;
        shell->count_tab = 0;
		shell->auto_active = 0;
		shell->multiauto_active = 0;
	}
	if (c == BACKSPACE)
	{
        ft_init_simple_autocompl(shell, env);
        shell->count_tab = 0;
		shell->auto_active = 0;
		shell->multiauto_active = 0;
        shell->keyflag->backspace = 1;
		shell->autocompl->can_print = 0;
		if (!ft_del_caractere(tmp, shell, env))
			return (0);
	}
    else if (c == UP && !shell->quotes)
		ft_move_history(shell, &shell->history->current, 2, env);
	else if (c == DOWN && !shell->quotes)
		ft_move_history(shell, &shell->history->current, 1, env);
	else if (!ft_other_key(tmp, shell, c, env))
		return (0);
	return (1);
}
