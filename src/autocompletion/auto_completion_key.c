#include "../../inc/autocompletion.h"

void    ft_autoMove(t_lineterm *end, t_shell *shell, t_env *env, int direction) //0left 1right
{
    int         i;
    int         jump;
	int			last_word;
	int			index;
    t_autocompl *tmp;
    (void)end;

    if (!shell->autocompl->current ||
			shell->len_prompt >= (int)get_columns())
        return ;
    shell->autocompl->arrow = 1;
    ft_free_dlist(&shell->line); 
    ft_init_console(shell, shell->line, env);
	if (shell->autocompl->can_print < 1)
	{
    	ft_cpy_autocompl_to_lineshell(shell);
		shell->autocompl->can_print++;
		return ;
	}
    i = -1;
    tmp = NULL;
    jump = (ft_count(shell->autocompl) / shell->autocompl->col) + 1;
	if (shell->autocompl->current)
    {
        tmp = shell->autocompl->current;
        while (tmp && ++i < jump)
            tmp = !direction ? tmp->prev : tmp->next;
    }
    if(!tmp)
    {
		last_word = (int)(((int)(shell->autocompl->end->index / jump)) * jump);
		tmp = shell->autocompl->current;
		if (!direction)
			index = (tmp->index == 1) ? (tmp->index + (jump * (shell->autocompl->col - 2))) :
				(tmp->index - 1 + jump * (shell->autocompl->col - 2));
		else
			index = (tmp->index == last_word) ? jump : (tmp->index - (jump * ((int)(tmp->index / jump))) + 1);
		ft_putnbr(index);
		while (tmp &&  tmp->index != index)
			tmp = !direction ? tmp->next : tmp->prev;
		if (tmp)
			shell->autocompl->current = tmp;
	}
    else
        shell->autocompl->current = tmp;
    ft_cpy_autocompl_to_lineshell(shell);
	shell->autocompl->can_print = 2;
}

void    ft_auto_down_up(t_lineterm *end, t_shell *shell, t_env *env, int direction)
{
    (void)end;

    if (!shell->autocompl->current
			|| shell->len_prompt >= (int)get_columns())
        return ;
    shell->autocompl->arrow = 1;
    ft_free_dlist(&shell->line); 
    ft_init_console(shell, shell->line, env);
	if (shell->autocompl->can_print < 1)
	{
    	ft_cpy_autocompl_to_lineshell(shell);
		shell->autocompl->can_print++;
		return ;
	}
    if (shell->autocompl->current && shell->autocompl->current->next 
			&& direction)
        shell->autocompl->current = shell->autocompl->current->next;
	else if (shell->autocompl->current && shell->autocompl->current->prev
			&& !direction)
        shell->autocompl->current = shell->autocompl->current->prev;
    else
	{
        shell->autocompl->current = (direction) ? 
			shell->autocompl->begin : shell->autocompl->end;
	}
    ft_cpy_autocompl_to_lineshell(shell);
	shell->autocompl->can_print = 2;
}
