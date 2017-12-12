#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"

void    ft_move_up_line(t_lineterm *end, t_termc *tsh)
{
    size_t col;

    if (tsh->auto_active == 1 || tsh->multiauto_active == 1)
        return ;
    tsh->history->down = 0;
    tsh->history->up = 0;
    col = get_columns() - 1;
    if (end->prev)
    {
        while (end->prev && end->index != 0 && col > 0)
        {
            end->s_pos = 0;
            end->prev->s_pos = 1;
            end = end->prev;
            col--;
        }
        tsh->line->last = 0;
    }
}

void    ft_move_down_line(t_lineterm *end, t_termc *tsh)
{
    size_t col;

    if (tsh->auto_active == 1 || tsh->multiauto_active == 1)
	{
		ft_auto_down_up(end, tsh, 1);
        return ;
	}
    tsh->history->down = 0;
    tsh->history->up = 0;
    col = get_columns() - 1;
    if (end->next)
    {
        while (end->next && col > 0)
        {
            end->s_pos = 0;
            end->next->s_pos = 1;
            end = end->next;
            col--;
        }
    }
	if (!end->next)
        tsh->line->last = 1;
}

static void	ft_move_history_split(t_termc *tsh, t_history **current, int flag)
{
    tsh->history->down = 0;
    tsh->history->up = 0;
    if ((*current)->next && flag == 1)
    {
        *current = (*current)->next;
        tsh->history->down = 1;
    }
    if ((*current)->prev && flag == 2)
    {
        *current = (*current)->prev;
        tsh->history->up = 1;
    }
}

static int ft_passed_or_not(t_termc *tsh)
{
	t_lineterm *begin;

	begin = tsh->line->begin;
	while (begin)
	{
		if (begin->under)
		{
    		tsh->keyflag->underline = 1;
			return (0);
		}
		begin = begin->next;
	}
	return (1);
}

void	ft_move_history(t_termc *tsh, t_history **current, int flag)
{
    int i;

    if (tsh->auto_active == 1 || tsh->multiauto_active == 1)
    {
		(flag == 1) ? ft_auto_down_up(NULL, tsh, 1) :
            ft_auto_down_up(NULL, tsh, 0);
		return ;
    }
    tsh->line->last = 1;
    if (!(*current) || !ft_passed_or_not(tsh))
        return ;
    ft_move_history_split(tsh, current, flag);
    tsh->history->active = 1;
    if (ft_count_dlnk(tsh) >= 1)
    {
        ft_free_dlist(&tsh->line);
        ft_init_console(tsh, tsh->line);
    }
    i = -1;
    while ((*current)->data[++i])
        ft_fill_back_dlst(tsh->line, (*current)->data[i], i + 2);
    tsh->line->last = 1;
}
