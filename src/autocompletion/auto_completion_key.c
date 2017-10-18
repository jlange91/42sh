#include "../../inc/autocompletion.h"

void    ft_autoleft(t_lineterm *end, t_shell *shell)
{
    int         i;
    int         jump;
    int         ret;
    t_autocompl *tmp;
    (void)end;

    if (!shell->autocompl->current
			|| shell->len_prompt >= (int)get_columns())
        return ;
    shell->autocompl->arrow = 1;
    ft_free_dlist(&shell->line); 
    ft_init_console(shell, shell->line);
    i = -1;
    tmp = NULL;
    jump = ft_count(shell->autocompl) / shell->autocompl->col;
    if (shell->autocompl->current && shell->autocompl->current->prev)
    {
        if (jump >= shell->autocompl->row + 4)
            jump = shell->autocompl->row - 1;
        tmp = shell->autocompl->current;
        while (tmp && ++i < jump + 1)
            tmp = tmp->prev;

    }
    if (!tmp)
    {
        int ret2;

        ret = 0;
        ret2 = 0;
        tmp = shell->autocompl->current;
        i = -1;
        ret = jump - tmp->index;
        if (ret < 0)
            ret = jump;
        ret2 = ft_count(shell->autocompl) - ret;
        while (tmp && tmp->index != ret2)
            tmp = tmp->next;
        if (tmp)
            shell->autocompl->current = tmp;
    }
    else
        shell->autocompl->current = tmp;
    ft_cpy_autocompl_to_lineshell(shell);
}

void    ft_autoright(t_lineterm *end, t_shell *shell)
{
    int         i;
    int         jump;
    int         ret;
    t_autocompl *tmp;
    (void)end;

    if (!shell->autocompl->current ||
			shell->len_prompt >= (int)get_columns())
        return ;
    shell->autocompl->arrow = 1;
    ft_free_dlist(&shell->line); 
    ft_init_console(shell, shell->line);
    i = -1;
    tmp = NULL;
    jump = ft_count(shell->autocompl) / shell->autocompl->col;
    if (shell->autocompl->current && shell->autocompl->current->next)
    {
        if (jump >= shell->autocompl->row + 4)
            jump = shell->autocompl->row - 1;
        tmp = shell->autocompl->current;
        while (tmp && ++i < jump + 1)
            tmp = tmp->next;
    }
    if(!tmp)
    {
        ret = 0;
        tmp = shell->autocompl->current;
        i = -1;
        ret = ft_count(shell->autocompl) - tmp->index;
        if (ret == jump)
            ret++;
        else
            ret = jump - ret;
        while (tmp && tmp->index != ret)
            tmp = tmp->prev;
        if (tmp)
            shell->autocompl->current = tmp;
    }
    else
        shell->autocompl->current = tmp;
    ft_cpy_autocompl_to_lineshell(shell);
}

void    ft_auto_down(t_lineterm *end, t_shell *shell)
{
    (void)end;

    if (!shell->autocompl->current
			|| shell->len_prompt >= (int)get_columns())
        return ;
    shell->autocompl->arrow = 1;
    ft_free_dlist(&shell->line); 
    ft_init_console(shell, shell->line);
    if (shell->autocompl->current && shell->autocompl->current->next)
        shell->autocompl->current = shell->autocompl->current->next;
    else
        shell->autocompl->current = shell->autocompl->begin;
    ft_cpy_autocompl_to_lineshell(shell);
}

void    ft_auto_up(t_lineterm *end, t_shell *shell)
{
    (void)end;

    if (!shell->autocompl->current
			|| shell->len_prompt >= (int)get_columns())
        return ;
    shell->autocompl->arrow = 1;
    ft_free_dlist(&shell->line); 
    ft_init_console(shell, shell->line);
    if (shell->autocompl->current && shell->autocompl->current->prev)
        shell->autocompl->current = shell->autocompl->current->prev;
    else
        shell->autocompl->current = shell->autocompl->end;
    ft_cpy_autocompl_to_lineshell(shell);
}
