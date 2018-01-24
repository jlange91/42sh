/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_readline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 19:24:21 by stvalett          #+#    #+#             */
/*   Updated: 2018/01/23 15:33:52 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/line_edition.h"
#include "../../inc/quote.h"

void			push_backdlst(dlist *line, int c, int i)
{
	t_lineterm	*new;

	new = NULL;
	if ((new = (t_lineterm *)malloc(sizeof(t_lineterm))) == NULL)
		exit(1);
	new->c = (char)c;
	new->under = 0;
	new->index = i;
	new->s_pos = 1;
	new->next = NULL;
	new->prev = line->end;
	if (line->end)
		line->end->next = new;
	else
		line->begin = new;
	line->end = new;
}

void			push_backhist(hlist *h, const char *str, int index, int n)
{
	t_history	*new;

	new = NULL;
	if ((new = (t_history *)malloc(sizeof(t_history))) == NULL)
		exit(1);
	new->data = ft_strdup((char *)str);
	new->index = index;
	new->print = 1;
	new->new = n;
	new->next = NULL;
	new->prev = h->end;
	if (h->end)
		h->end->next = new;
	else
		h->begin = new;
	h->end = new;
}

t_lineterm		*find_cursor(t_lineterm *end, int flag)
{
	if (flag)
	{
		if (!end->prev)
			return (end);
		while (end->prev->s_pos == 0)
			end = end->prev;
		return (end);
	}
	else
	{
		if (!end)
			return (NULL);
		if (end && end->index == 0)
			return (end);
		while (end->s_pos == 0)
			end = end->prev;
		return (end);
	}
}

int				ft_count_dlnk(t_termc *tsh, int q)
{
	t_lineterm	*tmp;
	int			i;

	tmp = tsh->line->begin;
	tmp = (tmp->next && q) ? ft_ps2(tmp) : ft_ps1(tmp);
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void			ft_insert_dlnk(t_lineterm *end, t_termc *tsh, int c, int i)
{
	t_lineterm	*new;

	end = find_cursor(end, 1);
	if (end->index == 0)
	{
		push_backdlst(tsh->line, c, i);
		tsh->line->last = 1;
		return ;
	}
	new = NULL;
	if ((new = (t_lineterm *)malloc(sizeof(t_lineterm))) == NULL)
		exit(1);
	new->c = (char)c;
	new->under = 0;
	new->s_pos = 1;
	new->index = i;
	new->next = end;
	new->prev = end->prev;
	end->prev->next = new;
	end->prev = new;
}
