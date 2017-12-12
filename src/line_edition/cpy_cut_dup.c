#include "../../inc/line_edition.h"

static void	ft_reset_under(t_termc *tsh)
{
	t_lineterm	*end;

	end = tsh->line->end;
	if (end)
	{
		while (end)
		{
			if (end->under == 1)
				end->under = 0;
			end = end->prev;
		}
	}
}

t_lineterm	*ft_cut_split(t_lineterm *tmp, t_termc *tsh)
{
	t_lineterm *del;

	ft_fill_back_dlst(tsh->line_dup, tmp->c, 2);
	del = tmp;
	tsh->keyflag->backspace = 1;
	if (tmp->next == NULL)
	{
		tsh->line->end = tmp->prev;
		tsh->line->end->next = NULL;
	}
	else if (tmp->prev == NULL)
	{
		tsh->line->begin = tmp->next;
		tsh->line->begin->prev = NULL;
	}
	else
	{
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
	}
	tmp = tmp->next;
	free(del);
	return (tmp);
}

void    ft_cut_line(t_lineterm *end, t_termc *tsh)
{
	t_lineterm  *tmp;
	int			ret;

	(void)end;
	ret = 1;
	tmp = tsh->line->begin;
	if (tmp != NULL)
	{
		if (tsh->line_dup->begin)
			ft_free_dlist(&tsh->line_dup);
		while (ret)
		{
			while (tmp && tmp->under == 0)
				tmp = tmp->next;
			while (tmp && tmp->under)
				tmp = ft_cut_split(tmp, tsh);
			if (!tmp)
				ret = 0;
		}
	}
	if (end->next == NULL)
		tsh->line->last = 1;
	else
		tsh->line->last = 0;
}

void	ft_dup_line(t_lineterm *end, t_termc *tsh)
{
	int			i;
	t_lineterm	*begin;

	(void)end;
	i = 1;
	if (tsh->line_dup->begin)
		ft_free_dlist(&tsh->line_dup);
	begin = tsh->line->begin;
	if (begin)
		while (begin)
		{
			if (begin->under == 1)
				ft_fill_back_dlst(tsh->line_dup, begin->c, i++);
			i++;
			begin = begin->next;
		}
	ft_reset_under(tsh);
}

void	ft_past_line(t_lineterm *end, t_termc *tsh)
{
	int			i;
	t_lineterm 	*begin;

	begin = tsh->line_dup->begin;
	if (begin)
	{
		i = 1;
		if (!end->next)
			while (begin)
			{
				ft_fill_back_dlst(tsh->line, begin->c, i++);
				begin = begin->next;
			}
		else
			while (begin)
			{
				ft_insert_dlnk(tsh->line->end, tsh, begin->c, i++);
				begin = begin->next;
			}
	}
}
