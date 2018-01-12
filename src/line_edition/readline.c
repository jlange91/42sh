/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <stvalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 19:23:56 by stvalett          #+#    #+#             */
/*   Updated: 2018/01/12 16:52:47 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"
#include "../../inc/globbing.h"
#include "../../inc/quote.h"

t_termc		*ft_ret_tsh(t_termc **arg)
{
	static t_termc *tsh = NULL;

	if (arg && *arg)
		tsh = *arg;
	return (tsh);
}

static void 	ft_ctr_d(t_termc *tsh)
{
	t_lineterm *end;

	if (tsh->auto_active || tsh->multiauto_active)
		return ;
	if (ft_count_dlnk(tsh, 0) >= 1)
	{
		end = find_cursor(tsh->line->end, 0);
		if (end && end->next)
		{
			end->next->under = 1;
			ft_cut_line(end, tsh);
		}
	}
	else
	{
		ft_putchar('\n');
		ft_end_term(tsh);
		exit(1);
	}
}

static int    	ft_key_and_char(t_termc *tsh, long c)
{
	if ((char)c == '\n' && !tsh->keyflag->k_tab)
	{
		if (!ft_line_quotes(tsh))
			return (ft_reset_line(tsh));
		return (1);
	}
	if ((char)c == EOT)
		ft_ctr_d(tsh);
	if (c == CL && !tsh->auto_active && !tsh->multiauto_active) 			// BOUCLE INFINI CHECK WHY !!!!!
		return (ft_save_line(tsh));
	if ((ft_is_key(tsh->line, tsh, c) == 0 && ft_isprint((char)c)))
	{
		tsh->auto_active = 0;
		tsh->multiauto_active = 0;
		tsh->keyflag->k_tab = 0;
		if (tsh->line->lnk_before)
			ft_insert_dlnk(tsh->line->end, tsh, c, 1);
		else
			push_backdlst(tsh->line, c, 1);
		if (ft_isprint((char)c) && c != BACKSPACE && c
				!= LEFT && c != RIGHT && c != UP && c != DOWN)
			ft_find_history(tsh);
	}
	else
		tsh->line->lnk_before = 1;
	if (tsh->line->last)
		tsh->line->lnk_before = 0;
	return (1);
}

static void	ft_init_readline(t_termc *tsh)
{
	t_lineterm 	*tmp;
	int 		i;

	tsh->line->lnk_before = 0;
	tsh->autoc->jump = 0;
	tsh->autoc->updaterow = 0;
	ft_init_console(tsh, tsh->line);
	ft_init_simple_autocompl(tsh);
	if (tsh->repl)
	{
		i = 0;
		while (tsh->replace[i])
		{
			push_backdlst(tsh->line, tsh->replace[i], 1);
			i++;
		}
		tsh->repl = 0;
		ft_strdel(&tsh->replace);
	}
	ft_display_char(tsh->line->begin, tsh);
	if (tsh->keyflag->cl)
	{
		tputs(tsh->term->clrstr, 1, ft_inputstr);
		ft_display_prompt(tsh);
		tmp = tsh->line_dup->begin;
		while (tmp)
		{
			push_backdlst(tsh->line, tmp->c, 1);
			tmp = tmp->next;
		}
		ft_display(tsh);
	}
}

/*******************************************************************************
 * FUNCTION HEART
 * ALL VARIABLE				ret ===> how time cursor jump
 * 							nbr ===> total number from line, for good malloc
 * 							in function ft_getstr
 *
 * 	Explication : read input caractere and check if is key or cactere and display
 *
 * 	NO NORME
 * 	***************************************************************************/

static void 	ft_split_arrow(long *c, int *stp, char k)
{
	*c = (k == 68 && *stp == 1) ? LEFT : *c;
	*c = (k == 67 && *stp == 1) ? RIGHT : *c;
	*c = (k == 65 && *stp == 1) ? UP : *c;
	*c = (k == 66 && *stp == 1) ? DOWN : *c;
	*c = (k == -102 && *stp == 3) ? OPT_V : *c;
	*c = (k == -89 && *stp == 1) ? OPT_C : *c;
	*c = (k == -120 && *stp == 3) ? OPT_X : *c;
	*c = (k == 72 && *stp == 1) ? HOME : *c;
	*c = (k == 70 && *stp == 1) ? END : *c;
	*c = (k == 68 && *stp == 2) ? OPT_F : *c;
	*c = (k == 67 && *stp == 2) ? OPT_B : *c;
	*c = (k == 65 && *stp == 2) ? OPT_UP : *c;
	*c = (k == 66 && *stp == 2) ? OPT_DOWN : *c;
	*c = (k == 68 && *stp == 4) ? MAJ_LEFT : *c;
	*c = (k == 67 && *stp == 4) ? MAJ_RIGHT : *c;
	*stp = 0;

}

int 	ft_what_arrow(long *c, int *stp, char k)
{
	if (k == 27 || k == -30 || k == -61)
	{
		return ((*stp = *stp + 1));
		return (1);
	}
	if (k == 91 || (k == -119 && *stp != 3) || (k == -120 && *stp != 3))
	{
		if (k == -120 || k == -119)
			*stp = 3;
		return (*stp);
	}
	if (*stp && (k == 49 || k == 59 || k == 50))
	{
		return ((*stp = 4));
		return (1);
	}
	if (*stp && (k == 68 || k == 67 || k == 65 || k == 66 || k == -102\
				|| k == 72 || k == 70 || k == -120 || k == -89))
		ft_split_arrow(c, stp, k);
	else
		*c = k;
	return (0);
}

char    *ft_readline(t_termc *tsh)
{
	char 	k;
	long 	c;
	static int stop;

	if (isatty(0))
	{
		ft_init_readline(tsh);
		ft_clean_all_letter(-1, -1);
		ft_singleton_down(0);
		while (read(0, &k, sizeof(k)))
		{
			if (ft_what_arrow(&c, &stop, k))
				continue ;
			if (!ft_key_and_char(tsh, c))
				break;
			ft_display(tsh);
			tsh->keyflag->backspace = 0;
			tsh->keyflag->underline = 0;
			tsh->keyflag->mleft = 0;
			tsh->repl = 0;
			tsh->sigint = 0;
		}
		return (ft_to_str(tsh, 0));
	}
	return (NULL);
}
