/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_print_autocompletion.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 19:04:43 by vmartins          #+#    #+#             */
/*   Updated: 2018/01/23 17:20:45 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/autocompletion.h"

/*
**@function
**@param
**@return
*/

int					ft_cursor_update(void)
{
	int				fd;
	int				row;

	fd = ft_current_tty();
	if (fd == -1)
		return (1);
	row = 0;
	ft_cursor_position(fd, &row);
	close(fd);
	return (row);
}

/*
**@function
**@param
**@return
*/

int					ft_getcursor(int i, int res, t_termc *tsh)
{
	static int		ret;

	if (i == 0 && res == 0)
		ret = ft_cursor_update();
	else if (!tsh->autoc->arrow && ret != res)
		ret = ft_cursor_update();
	return (ret);
}

/*
**@function
**@param
**@return
*/

void				ft_display_autocompletion(t_termc *tsh)
{
	int				i;

	if (tsh->len_prompt >= (int)get_columns())
		return ;
	i = -1;
	tsh->line->last = 1;
	tsh->autoc->jump = 0;
	ft_menu_autocompletion(tsh->autoc, tsh);
	if (tsh->autoc->clr_yes)
		tputs(tgoto(tgetstr("cm", NULL), 0, tsh->autoc->updaterow - 1),
				1, ft_inputstr);
	tsh->autoc->clr_yes = 0;
}

/*
**@function
**			select->max_len = MAX LEN WORD WE CAN FIND
**			select->row = GET_LINE MAX DISPLAY ON SCREEN
**			select->col = GET_NUMBER COL
**			select->pages = HOW MANY PAGES WE CAN DISPLAY
**			select->pages = IF REST MORE PAGES
**			select->nbr_word = MAX WORD ON SCREEN
**@param
**@return
*/

int					ft_init_value(t_termc *tsh, t_auto *select)
{
	struct winsize	row;

	ioctl(0, TIOCGWINSZ, &row);
	select->max_len = ft_max_len(select);
	select->row = row.ws_row - 4;
	select->col = (int)((int)(row.ws_col / (select->max_len + 2)));
	if (select->col == 0)
		return (0);
	select->jump = (ft_count(select) / select->col) + 1;
	select->pages = tsh->autoc->jump / select->row;
	select->more_pages = tsh->autoc->jump % select->row;
	select->nbr_word = (select->row * select->col);
	return (1);
}

/*
**@function
**@param
**@return
*/

int					ft_max_len(t_auto *select)
{
	t_autocompl		*begin;
	int				count;

	count = ft_strlen(select->begin->data);
	begin = select->begin->next;
	while (begin)
	{
		if (ft_strlen(begin->data) > count)
			count = ft_strlen(begin->data);
		begin = begin->next;
	}
	return (count);
}
