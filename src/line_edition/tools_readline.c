/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_readline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 19:24:21 by stvalett          #+#    #+#             */
/*   Updated: 2017/08/29 14:06:27 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/line_edition.h"

void    ft_fill_back_dlst(dlist *line, int c, int i)
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
    {
        line->begin = new;
    }
	line->end = new;
}

void    ft_fill_back_hlst(hlist *h, const char *str)
{
	t_history	*new;

	new = NULL;
	if ((new = (t_history *)malloc(sizeof(t_history))) == NULL)
		exit(1);
	new->data = ft_strdup((char *)str);
	new->next = NULL;
	new->prev = h->end;
	if (h->end)
		h->end->next = new;
	else
		h->begin = new;
	h->end = new;
}

static inline t_lineterm *get_cursor_current(t_lineterm *end)
{
	if (!end->prev)
		return (end);
	while (end->prev->s_pos == 0)
		end = end->prev;
	return (end);
}

int		ft_count_dlnk(t_termc *tsh)
{
	t_lineterm *tmp;
	int			i;

	tmp = tsh->line->begin;
	if (tmp->next)
		tmp = ft_dontGetPrompt2(tmp);
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void  ft_insert_dlnk(t_lineterm *end, t_termc *tsh, int c, int i)
{
	t_lineterm  *new;

	end = get_cursor_current(end);
	if (end->index == 0)
	{
		ft_fill_back_dlst(tsh->line, c, i);
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
	tsh->line->lenght += 1;
}
