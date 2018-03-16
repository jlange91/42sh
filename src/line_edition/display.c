/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 17:55:17 by vmartins          #+#    #+#             */
/*   Updated: 2018/01/30 16:09:13 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"

static	inline	int		ft_cursor_pos(t_lineterm *end, t_termc *tsh)
{
	int					up;
	int					i;

	up = 0;
	if (!end)
		return (-1);
	while (end->s_pos == 0 && end->index != 0)
	{
		if ((tsh->console->char_pos == 0 || end->c == '\n') && end->prev)
		{
			tputs(tsh->term->upstr, 1, ft_inputstr);
			tsh->console->char_pos = get_columns() - 1;
			if (!ft_ret_ligne(end, tsh))
			{
				i = -1;
				while (++i < (int)get_columns() - 1)
					tputs(tsh->term->ndstr, 1, ft_inputstr);
			}
			up++;
		}
		tputs(tsh->term->lestr, 1, ft_inputstr);
		tsh->console->char_pos--;
		end = end->prev;
	}
	return (up);
}

static	inline	void	ft_del_line(t_termc *t)
{
	int					down;

	down = ft_ret_down(-1);
	while (down-- > 0)
		tputs(t->term->dostr, 1, ft_inputstr);
	t->console->total_line--;
	if (t->console->total_line > 0)
		while (t->console->total_line--)
			tputs(t->term->upstr, 1, ft_inputstr);
	while (t->console->char_pos--)
		tputs(t->term->lestr, 1, ft_inputstr);
}

static	void			ft_display_char_split(t_lineterm *begin, t_termc *tsh)
{
	size_t				col;

	col = get_columns() - 1;
	if (begin->index == 0 && !tsh->quotes)
		ft_putstr(tsh->color[tsh->prompt]);
	else
		ft_putstr(RESET);
	if (tsh->console->char_pos == col || begin->c == '\n')
	{
		if (begin->c == '\n')
			tputs(tsh->term->cestr, 1, ft_inputstr);
		tputs(tsh->term->dostr, 1, ft_inputstr);
		tsh->console->total_line++;
		tsh->console->char_pos = 0;
	}
	if (begin->under)
		ft_putstr(tsh->color[tsh->linep]);
	if (begin->c != '\t' && begin->c != '\n')
		ft_putchar(begin->c);
	tsh->console->char_pos++;
	ft_putstr(RESET);
}

int						ft_display_char(t_lineterm *begin, t_termc *tsh)
{
	tsh->console->char_pos = 0;
	tsh->console->total_line = 1;
	while (begin)
	{
		ft_display_char_split(begin, tsh);
		begin = begin->next;
	}
	if (tsh->auto_active || tsh->multiauto_active)
		tputs(tsh->term->cestr, 1, ft_inputstr);
	else
		tputs(tsh->term->cdstr, 1, ft_inputstr);
	return (0);
}

void					ft_display(t_termc *tsh)
{
	tputs(tsh->term->vistr, 1, ft_inputstr);
	ft_del_line(tsh);
	ft_display_char(tsh->line->begin, tsh);
	ft_ret_down(ft_cursor_pos(tsh->line->end, tsh));
	if ((tsh->auto_active || tsh->multiauto_active)\
			&& tsh->console->total_line < 2 && !tsh->sigint)
	{
		ft_display_autocompletion(tsh);
		return ;
	}
	tputs(tsh->term->vestr, 1, ft_inputstr);
}
