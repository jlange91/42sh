/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <stvalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 19:23:56 by stvalett          #+#    #+#             */
/*   Updated: 2018/01/23 14:55:06 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"
#include "../../inc/globbing.h"
#include "../../inc/quote.h"
#include "../../inc/sh21.h"

static	void	ft_insert_char(t_termc *tsh, long c)
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

static	int		ft_key_or_insert(t_termc *tsh, long c)
{
	if ((char)c == '\n' && !tsh->keyflag->k_tab)
	{
		if (!ft_line_quotes(tsh))
			return (ft_reset_line(tsh));
		return (1);
	}
	if ((char)c == EOT)
		ft_ctr_d(tsh);
	if (c == CL && !tsh->auto_active && !tsh->multiauto_active)
		return (ft_save_line(tsh));
	if ((!ft_action_key(tsh->line, tsh, c) && ft_isprint((char)c)))
		ft_insert_char(tsh, c);
	else
		tsh->line->lnk_before = 1;
	if (tsh->line->last)
		tsh->line->lnk_before = 0;
	return (1);
}

static	void	ft_print_diff_mode(t_termc *tsh, int mode)
{
	t_lineterm	*tmp;
	int			i;

	if (mode == REPLACE && tsh->repl)
	{
		i = -1;
		while (tsh->replace[++i])
			push_backdlst(tsh->line, tsh->replace[i], 1);
		tsh->repl = 0;
		ft_strdel(&tsh->replace);
	}
	else if (mode == CTR_L && tsh->keyflag->cl)
	{
		tputs(tsh->term->clrstr, 1, ft_inputstr);
		ft_display_prompt(tsh);
		tmp = tsh->line_dup->begin;
		while (tmp)
		{
			push_backdlst(tsh->line, tmp->c, 1);
			tmp = tmp->next;
		}
		ft_free_dlist(&tsh->line_dup);
		ft_display(tsh);
	}
}

static	void	ft_init_readline(t_termc *tsh)
{
	tsh->line->lnk_before = 0;
	tsh->autoc->jump = 0;
	tsh->autoc->updaterow = 0;
	ft_init_console(tsh, tsh->line);
	ft_init_simple_autocompl(tsh, 0, NULL);
	ft_print_diff_mode(tsh, REPLACE);
	ft_display_char(tsh->line->begin, tsh);
	ft_print_diff_mode(tsh, CTR_L);
}

char			*ft_readline(t_termc *tsh)
{
	char		k;
	long		c;
	static int	stop;

	if (isatty(0))
	{
		ft_init_readline(tsh);
		ft_clean_all_letter(-1, -1);
		ft_ret_down(0);
		while (read(0, &k, sizeof(k)))
		{
			if (ft_what_key(&c, &stop, k))
				continue ;
			if (!ft_key_or_insert(tsh, c))
				break ;
			ft_display(tsh);
			tsh->keyflag->underline = 0;
			tsh->repl = 0;
			tsh->sigint = 0;
		}
		return (ft_to_str(tsh, 0));
	}
	return (NULL);
}
