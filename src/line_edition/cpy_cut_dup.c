#include "../../inc/line_edition.h"

static void	ft_reset_under(t_termc *shell)
{
	t_lineterm	*end;

	end = shell->line->end;
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

void    ft_cut_line(t_lineterm *end, t_termc *shell, char **env)
{
	t_lineterm  *tmp;
	t_lineterm  *del;
	int			ret;
	int			i;

	(void)end;
	(void)env;
	ret = 1;
	i = 1;
	tmp = NULL;
	del = NULL;
	tmp = shell->line->begin;
	if (tmp != NULL)
	{
		if (shell->line_dup->begin)
			ft_free_dlist(&shell->line_dup);
		while (ret)
		{
			while (tmp && tmp->under == 0)
				tmp = tmp->next;
			while (tmp && tmp->under)
			{
				ft_fill_back_dlst(shell->line_dup, tmp->c, i++);
				del = tmp;
				shell->keyflag->backspace = 1;
				if (tmp->next == NULL)
				{
					shell->line->end = tmp->prev;
					shell->line->end->next = NULL;
				}
				else if (tmp->prev == NULL)
				{
					shell->line->begin = tmp->next;
					shell->line->begin->prev = NULL;
				}
				else
				{
					tmp->prev->next = tmp->next;
					tmp->next->prev = tmp->prev;
				}
				tmp = tmp->next;
				free(del);
			}
			if (!tmp)
				ret = 0;
		}
	}
	if (end->next == NULL)
		shell->line->last = 1;
	else
		shell->line->last = 0;
}

void	ft_dup_line(t_lineterm *end, t_termc *shell, char **env)
{
	int			i;
	t_lineterm	*begin;

	(void)end;
	(void)env;
	i = 1;
	if (shell->line_dup->begin)
		ft_free_dlist(&shell->line_dup);
	begin = shell->line->begin;
	if (begin)
		while (begin)
		{
			if (begin->under == 1)
				ft_fill_back_dlst(shell->line_dup, begin->c, i++);
			i++;
			begin = begin->next;
		}
	ft_reset_under(shell);
}

void	ft_past_line(t_lineterm *end, t_termc *shell, char **env)
{
	int			i;
	t_lineterm 	*begin;

	(void)env;
	begin = shell->line_dup->begin;
	if (begin)
	{
		i = 1;
		if (!end->next)
			while (begin)
			{
				ft_fill_back_dlst(shell->line, begin->c, i++);
				begin = begin->next;
			}
		else
			while (begin)
			{
				ft_insert_dlnk(shell->line->end, shell, begin->c, i++);
				begin = begin->next;
			}
	}
}
