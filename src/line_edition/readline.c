/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <stvalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 19:23:56 by stvalett          #+#    #+#             */
/*   Updated: 2017/11/17 10:02:15 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"
#include "../../inc/globbing.h"

t_termc		*ft_ret_tsh(t_termc **arg)
{
	static t_termc *tsh = NULL;

	if (arg && *arg)
		tsh = *arg;
	return (tsh);
}

/*******************************************************************************
 * FUNCTION GETSTR
 * ALL VARIABLE				nbr ==> for good malloc
 *
 *	EXPLICATION : this function transform double linked to string
 *
 * NO NORME
 ******************************************************************************/

static inline char  *ft_getstr(t_termc *tsh, t_lineterm *begin)
{
	t_lineterm *tmp;
	char        *str;
	int         i;

	tmp = begin;
	i = 0;
	str = NULL;
	if (!tmp)
		return (NULL);
	else if (tmp->next)
		tmp = ft_dontGetPrompt2(tmp);
	if ((str = (char *)malloc(sizeof(char) * ft_count_dlnk(tsh) + 1)) == NULL)
		return (NULL);
	while (tmp)
	{
		str[i++] = tmp->c;
		tmp = tmp->next;
	}
	str[i] = '\0';
	if (ft_strlen(str) >= 1)
		ft_add_tmp_history(tsh, str);
	return (str);
}

static int    ft_key_and_char(t_termc *tsh, long c)
{
	if ((char)c == '\n' && !tsh->keyflag->k_tab)
		return (ft_reset_line(tsh));
	if (c == CL && !tsh->auto_active && !tsh->multiauto_active)
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

static void	ft_line_input_split(t_termc *tsh)
{
	t_lineterm *tmp;

	tsh->line->lnk_before = 0;
	tsh->autoc->jump = 0;
	tsh->quotes = 0;
	tsh->autoc->updaterow = 0;
	ft_init_console(tsh, tsh->line);
	ft_init_simple_autocompl(tsh);
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
		ft_display(tsh, 0);
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
char    *ft_line_input(t_termc *tsh)
{
	long 	c;

	if (isatty(0))
	{
		c = 0;
		ft_line_input_split(tsh);
		ft_clean_all_letter(-1, -1);
		while (read(0, &c, sizeof(c)))
		{
			if (!ft_key_and_char(tsh, c))
				break;
			ft_display(tsh, 0);
			c = 0;
			tsh->keyflag->backspace = 0;
			tsh->keyflag->underline = 0;
			tsh->keyflag->mleft = 0;
			tsh->repl = 0;
			tsh->sigint = 0;
		}
		return (ft_getstr(tsh, tsh->line->begin));
	}
	return (NULL);
}
