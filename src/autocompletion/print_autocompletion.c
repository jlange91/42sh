/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_autocompletion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 18:44:52 by stvalett          #+#    #+#             */
/*   Updated: 2018/01/23 19:17:53 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/autocompletion.h"
#include "../../inc/line_edition.h"

/*
**@function	Check line and get new result in struct var and update cursor
**			in select->updaterow
**			The last condition "IF" we are 3 lines before the end of windows
**			terms
**@param
**@return
*/

static	void	ft_check_line_simple(t_auto *select, t_var_auto *var)
{
	if (var->ttl_jump > 0)
	{
		ft_putchar('\n');
		if (var->row++ >= select->row + 4)
			var->down++;
		var->ttl_jump--;
	}
	if (var->ttl_jump == 0)
	{
		if (var->len + select->max_len + 2 < (int)get_columns())
			var->len += select->max_len + 2;
		var->ttl_jump = select->jump;
		if (var->down != 0)
			var->row = select->updaterow - (var->down + 1);
		else
			var->row = select->updaterow;
		if (var->row - 2 == select->row && select->jump != 1)
		{
			select->updaterow--;
			var->row--;
		}
	}
	tputs(tgoto(tgetstr("cm", NULL), var->len, var->row), 1, ft_inputstr);
}

/*
**@function
**@param
**@return
*/

static	void	ft_print_simple_auto(t_auto *select, t_autocompl *begin)
{
	t_var_auto	*var;

	var = ft_init_var_auto(select);
	while (begin)
	{
		ft_check_line_simple(select, var);
		ft_display_autocompl(begin, select);
		begin = begin->next;
	}
	if (var->down != 0)
		select->updaterow = select->updaterow - (var->down + 1);
	select->clr_yes = 1;
	free(var);
}

/*
**@function
**@param	1 = struct select
**			2 = struct var_auto
**			3 = b is begin in struct autocompl
**			4 = limit_word
**@return
*/

static	int		pfsc(t_auto *select, t_var_auto *var, t_autocompl *b, int l_w)
{
	while (b && b->index <= l_w)
	{
		if (var->ttl_jump > 0)
		{
			ft_putchar('\n');
			var->row++;
			var->ttl_jump--;
		}
		if (var->ttl_jump == 0)
		{
			if (var->len + select->max_len + 2 < (int)get_columns() - 1)
				var->len += select->max_len + 2;
			var->ttl_jump = select->jump;
			var->row = select->updaterow;
		}
		tputs(tgoto(tgetstr("cm", NULL), var->len, var->row), 1, ft_inputstr);
		ft_display_autocompl(b, select);
		b = b->next;
	}
	return (0);
}

/*
**@function
**@param	1 = struct t_auto select
**			2 = b begin from struct autocompl
**			3 =
**			4 =
**@return
*/

void			ft_diff_print(t_auto *select, t_autocompl *b, int nbr, int flag)
{
	t_var_auto	*var;
	int			limit_word;

	if (flag == 2)
	{
		var = ft_init_var_auto(select);
		limit_word = select->jump * select->col * nbr;
		pfsc(select, var, b, limit_word);
		free(var);
		select->clr_yes = 1;
	}
	else
		ft_print_simple_auto(select, b);
}

/*
**@function
**@param
**@return
*/

void			ft_menu_autocompletion(t_auto *select, t_termc *tsh)
{
	t_autocompl	*begin;

	begin = select->begin;
	if (begin)
	{
		ft_init_value(tsh, select);
		if (tsh->autoc->jump > select->row)
			ft_mpages(select, tsh, begin);
		else
		{
			tsh->autoc->updaterow = ft_getcursor(0, tsh->autoc->updaterow, tsh);
			ft_diff_print(select, begin, 0, 1);
		}
		select->arrow = 0;
	}
}
