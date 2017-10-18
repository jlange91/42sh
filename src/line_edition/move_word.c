#include "../../inc/line_edition.h"

void    ft_move_begin(t_lineterm *end, t_shell *shell, t_env *env)
{
	(void)env;
    if (shell->auto_active)
        return ;
    shell->history->down = 0;
    shell->history->up = 0;
    if (end->prev)
    {
        while (end && end->index != 0)
        {
            end->s_pos = 0;
            if (end->next)
                end->next->s_pos = 0;
            end = end->prev;
        }
        shell->line->last = 0;
        end = end->next;
    }
}

void    ft_move_end(t_lineterm *end, t_shell *shell, t_env *env)
{
	(void)env;
    if (shell->auto_active)
        return ;
    shell->history->down = 0;
    shell->history->up = 0;
    if (end->next)
    {
        while (end)
        {
            end->s_pos = 1;
            if (end->prev && end->prev->index != 0)
                end->prev->s_pos = 0;
            end = end->next;
        }
        shell->line->last = 1;
    }
}

void    ft_move_word_forward(t_lineterm *end, t_shell *shell, t_env *env)
{
	(void)env;
    if (shell->auto_active)
        return ;
    shell->history->down = 0;
    shell->history->up = 0;
    while ((end->c == ' ' || end->c == '\t') && end && end->index != 0)
    {
        end->s_pos = 0;
        if (end->next)
            end->next->s_pos = 0;
        end = end->prev;
    }
    while (end->c != ' ' && end->c != '\t' && end && end->index != 0)
    {
        end->s_pos = 0;
        if (end->next)
            end->next->s_pos = 0;
        end = end->prev;
    }
    while (end && end->index != 0)
    {
        end->s_pos = 1;
        end = end->prev;
    }
    shell->line->last = 0;
}

void    ft_move_word_back(t_lineterm *end, t_shell *shell, t_env *env)
{
	(void)env;
    if (shell->auto_active)
        return ;
    shell->history->down = 0;
    shell->history->up = 0;
    while (end && ((char)end->c == ' ' || (char)end->c == '\n'))
    {
        end->s_pos = 1;
        if (end->prev && end->prev->index != 0)
            end->prev->s_pos = 0;
        end = end->next;
    }
    while (end && (char)end->c != ' ' && (char)end->c != '\n')
    {
        end->s_pos = 0;
        if (end->prev && end->prev->index != 0)
            end->prev->s_pos = 1;
        end = end->next;
    }
    while (end && ((char)end->c == ' ' || (char)end->c == '\n'))
    {
        end->s_pos = 1;
        if (end->prev && end->prev->index != 0)
            end->prev->s_pos = 0;
        end = end->next;
    }
}
