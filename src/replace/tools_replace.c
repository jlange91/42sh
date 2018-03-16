/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_replace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 15:59:02 by vmartins          #+#    #+#             */
/*   Updated: 2018/01/22 16:00:09 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"
#include "../../inc/globbing.h"
#include "../../inc/sh21.h"
#include "../../inc/quote.h"

void			push_dupdlst(t_dlst *line, t_lineterm *src)
{
	t_lineterm	*new;

	new = NULL;
	if ((new = (t_lineterm *)malloc(sizeof(t_lineterm))) == NULL)
		exit(1);
	new->c = src->c;
	new->under = src->under;
	new->index = src->index;
	new->s_pos = src->s_pos;
	new->next = NULL;
	new->prev = line->end;
	if (line->end)
		line->end->next = new;
	else
		line->begin = new;
	line->end = new;
}

void			ft_freedlnk(t_dlst *line)
{
	t_lineterm	*del;
	t_lineterm	*elem;

	elem = line->end;
	if (elem != NULL)
	{
		while (elem)
		{
			del = elem;
			elem = elem->prev;
			free(del);
		}
		line->begin = NULL;
		line->end = NULL;
		return ;
	}
}

void			ft_dupdlnk(t_dlst *line, t_dlst *tmp)
{
	t_termc		*tsh;
	t_lineterm	*begin;

	tsh = ft_ret_tsh(NULL);
	begin = line->begin;
	begin = (tsh->quotes || tsh->hdoc) ? ft_ps2(begin) :
	ft_ps1(begin);
	while (begin)
	{
		push_dupdlst(tmp, begin);
		begin = begin->next;
	}
}

void			ft_cpy_to_line(char *data, t_termc *tsh)
{
	int			i;

	i = -1;
	tsh->autoc->updaterow = 0;
	while (data[++i])
		push_backdlst(tsh->line, data[i], 1);
}

int				ft_word_here(t_lineterm *begin, char *word)
{
	int			i;

	i = 0;
	while (word[i])
	{
		if (word[i] == begin->c)
		{
			if (begin && begin->next)
				begin = begin->next;
		}
		else
			break ;
		i++;
	}
	if (word[i] == '\0' && ((begin && begin->s_pos == 0) || !begin->next))
		return (1);
	return (0);
}
