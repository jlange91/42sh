#include "../../inc/autocompletion.h"

static int  ft_reset_key(t_termc *tsh)
{
    if (!tsh->autoc->current || tsh->len_prompt >= (int)get_columns())
        return (0);
    tsh->autoc->arrow = 1;
    ft_clean_line(tsh);
	if (tsh->autoc->can_print < 1)
	{
    	ft_cpy_autocompl_to_lineshell(tsh);
		tsh->autoc->can_print++;
		return (0);
	}
    return (1);
}

static void     ft_auto_movesplit(t_termc *tsh, int dire, int jump)
{
    int last_word;
    int index;
    t_autocompl *tmp;

    last_word = 0;
    index = 0;
    last_word = (int)(((int)(tsh->autoc->end->index / jump)) * jump);
    tmp = tsh->autoc->current;
    if (!dire)
        index = (tmp->index == 1) ?
        (tmp->index + (jump * (tsh->autoc->col - 2))) :
        (tmp->index - 1 + jump * (tsh->autoc->col - 2));
    else
        index = (tmp->index == last_word) ? jump :
        (tmp->index - (jump * ((int)(tmp->index / jump))) + 1);
    while (tmp &&  tmp->index != index)
        tmp = !dire ? tmp->next : tmp->prev;
    if (tmp)
        tsh->autoc->current = tmp;
}

void    ft_autoMove(t_lineterm *end, t_termc *tsh, int direction) //0left 1right
{
    int         i;
    int         jump;
    t_autocompl *tmp;
    (void)end;

    if (!(ft_reset_key(tsh)))
        return ;
    i = -1;
    tmp = NULL;
    jump = (ft_count(tsh->autoc) / tsh->autoc->col) + 1;
	if (tsh->autoc->current)
    {
        tmp = tsh->autoc->current;
        while (tmp && ++i < jump)
            tmp = !direction ? tmp->prev : tmp->next;
    }
    if(!tmp)
        ft_auto_movesplit(tsh, direction, jump);
    else
        tsh->autoc->current = tmp;
    ft_cpy_autocompl_to_lineshell(tsh);
	tsh->autoc->can_print = 2;
}

void    ft_auto_down_up(t_lineterm *end, t_termc *tsh, int dire)
{
    (void)end;

    if (!(ft_reset_key(tsh)))
        return ;
    if (tsh->autoc->current && tsh->autoc->current->next && dire)
        tsh->autoc->current = tsh->autoc->current->next;
	else if (tsh->autoc->current && tsh->autoc->current->prev && !dire)
        tsh->autoc->current = tsh->autoc->current->prev;
    else
        tsh->autoc->current = (dire) ?
			tsh->autoc->begin : tsh->autoc->end;
    ft_cpy_autocompl_to_lineshell(tsh);
	tsh->autoc->can_print = 2;
}
