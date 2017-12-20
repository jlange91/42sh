#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"

void    ft_move_up_line(t_lineterm *end, t_termc *tsh)
{
    size_t col;

    if (tsh->auto_active == 1 || tsh->multiauto_active == 1)
        return ;
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

void    ft_move_down_line_auto(t_lineterm *end, t_termc *tsh)
{
    if (tsh->auto_active == 1 || tsh->multiauto_active == 1)
	{
		ft_auto_down_up(end, tsh, 1);
        return ;
	}
}

void    ft_move_down_line(t_lineterm *end, t_termc *tsh)
{
    size_t col;

    if (tsh->auto_active == 1 || tsh->multiauto_active == 1)
        return ;
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

static int	ft_move_history_split(t_history **current, int flag)
{
    int ret;

    ret = 0;
    if ((*current)->next && flag == 1)
    {
        *current = (*current)->next;
        ret = 1;
    }
    if ((*current)->prev && flag == 2)
    {
        *current = (*current)->prev;
        ret = 1;
    }
    return (ret);
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
    if (!(*current) || !ft_passed_or_not(tsh) ||
        !ft_move_history_split(current, flag) )
        return ;
    if (ft_count_dlnk(tsh) >= 1)
        ft_clean_line(tsh);
    i = -1;
    while ((*current)->data[++i])
        push_backdlst(tsh->line, (*current)->data[i], i + 2);
    tsh->line->last = 1;
}
