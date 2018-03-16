/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrow_key.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 15:10:48 by vmartins          #+#    #+#             */
/*   Updated: 2017/11/22 13:30:48 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static	void	ft_up_arrow(t_select **select)
{
	char		*cap;
	t_select	*s;

	s = *select;
	if ((cap = tgetstr("cl", NULL)) == NULL)
		ft_putendl("Cannot clean screen");
	else
		tputs(cap, 0, ft_putc);
	if (s->cursor_line == 1)
		s->cursor_line = s->nb_elem;
	else
		s->cursor_line--;
	ft_print_all(select, 0, 0);
}

static	void	ft_down_arrow(t_select **select)
{
	char		*cap;
	t_select	*s;

	s = *select;
	if ((cap = tgetstr("cl", NULL)) == NULL)
		ft_putendl("Cannot clean screen");
	else
		tputs(cap, 0, ft_putc);
	if (s->cursor_line == s->nb_elem)
		s->cursor_line = 1;
	else
		s->cursor_line++;
	ft_print_all(select, 0, 0);
}

void			ft_arrow_key(t_select **select, char *buf)
{
	t_select *s;

	s = *select;
	if (buf[2] == 'A')
		ft_up_arrow(select);
	if (buf[2] == 'B')
		ft_down_arrow(select);
}
