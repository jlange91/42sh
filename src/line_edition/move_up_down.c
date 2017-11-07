#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"

void    ft_move_up_line(t_lineterm *end, t_shell *shell, t_env *env)
{
    size_t col;

	(void)env;
    if (shell->auto_active == 1 || shell->multiauto_active == 1)
        return ;
    shell->history->down = 0;
    shell->history->up = 0;
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
        shell->line->last = 0;
    }
}

void    ft_move_down_line(t_lineterm *end, t_shell *shell, t_env *env)
{
    size_t col;

	(void)env;
    if (shell->auto_active == 1 || shell->multiauto_active == 1)
	{
		ft_auto_down_up(end, shell, env, 1);
        return ;
	}
    shell->history->down = 0;
    shell->history->up = 0;
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
        shell->line->last = 1;
}

static void	ft_move_history_split(t_shell *shell, t_history **current, int flag)
{
    shell->history->down = 0;
    shell->history->up = 0;
    if ((*current)->next && flag == 1)
    {
        *current = (*current)->next;
        shell->history->down = 1;
    }
    if ((*current)->prev && flag == 2)
    {
        *current = (*current)->prev;
        shell->history->up = 1;
    }
}

static int ft_passed_or_not(t_shell *shell)
{
	t_lineterm *begin;

	begin = shell->line->begin;
	while (begin)
	{
		if (begin->under)
		{
    		shell->keyflag->underline = 1;
			return (0);
		}
		begin = begin->next;
	}
	return (1);
}

void	ft_move_history(t_shell *shell, t_history **current, int flag, t_env *env)
{
    int i;

    if (shell->auto_active == 1 || shell->multiauto_active == 1)
    {
		(flag == 1) ? ft_auto_down_up(NULL, shell, env, 1) : 
            ft_auto_down_up(NULL, shell, env, 0);
		return ;
    }
    shell->line->last = 1;
    if (!(*current) || !ft_passed_or_not(shell))
        return ;
    ft_move_history_split(shell, current, flag);
    shell->history->active = 1;
    if (ft_count_dlnk(shell) >= 1)
    {
        ft_free_dlist(&shell->line); 
        ft_init_console(shell, shell->line, env);
    }
    i = -1;
    while ((*current)->data[++i])
        ft_fill_back_dlst(shell->line, (*current)->data[i], i + 2);
    shell->line->last = 1;
}
