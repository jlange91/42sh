/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 18:00:13 by stvalett          #+#    #+#             */
/*   Updated: 2018/01/23 15:22:39 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"

int					ft_ret_down(int len)
{
	static int		down;

	if (len == 0)
		down = 0;
	else if (len == -1)
		return (down);
	else if (down != len)
		down = len;
	return (down);
}

static	int			ft_move_next(t_lineterm *tmp)
{
	int				i;

	i = 0;
	while (tmp && (tmp = tmp->prev) && tmp->c != '\n')
		i++;
	i++;
	return (i);
}

int					ft_ret_ligne(t_lineterm *end, t_termc *tsh)
{
	unsigned long	k;
	int				i;
	t_lineterm		*tmp;

	if (end->c == '\n')
	{
		tmp = end;
		i = ft_move_next(tmp);
		k = -1;
		if (i >= (int)tsh->console->char_pos)
		{
			if (i % tsh->console->char_pos == 0)
				return (0);
			while (++k < i % tsh->console->char_pos + 1)
				tputs(tsh->term->ndstr, 1, ft_inputstr);
			tsh->console->char_pos = i % tsh->console->char_pos;
		}
		else
		{
			while (++k < i % get_columns())
				tputs(tsh->term->ndstr, 1, ft_inputstr);
		}
		return (1);
	}
	return (0);
}
