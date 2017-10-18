#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"

/************************************************************************************
 * FUNCTION MOVE_RIGHT OR MOVE_LEFT
 *
 * ALL VARIABLE			shell->history->down ===> reinitialise
 *						shell->history->up ===> reinitialise
 *						shell->end->s_pos ===> If cursor can be here or not
 *												if s_pos == 0 , cursor can be on the letter else can't
 *						shell->end->under ==> active underline caractere if keyflag->underline is active
 *						shell->line->last ==> if we are end of the double linked , we active this variable
 *												else we active shell->line->lnk_before
 *						
 *
 *	Explication : This function display caractere by caractere correctly
 *
 * NO NORME
 * *********************************************************************************/

void	ft_move_right(t_lineterm *end, t_shell *shell, t_env *env)
{
	(void)env;
    if (shell->auto_active || shell->multiauto_active)
    {
        ft_autoright(end, shell);
        return ;
    }
    shell->history->down = 0;
    shell->history->up = 0;
    shell->auto_active = 0;
    shell->multiauto_active = 0;
    if (end->next)
    {
        if (shell->keyflag->underline && end->under != 1)
            end->under = 1;
        end->s_pos = 0;
        end->next->s_pos = 1;
        if (!end->next->next)
            shell->line->last = 1;
        else
            shell->line->lnk_before = 1;
        shell->move_cursor = 1;
    }
}

void    ft_move_left(t_lineterm *end, t_shell *shell, t_env *env)
{
	(void)env;
    if (shell->auto_active || shell->multiauto_active)
    {
        ft_autoleft(end, shell);
        return ;
    }
    shell->history->down = 0;
    shell->history->up = 0;
    shell->auto_active = 0;
    shell->multiauto_active = 0;
    if (end->prev && end->index != 0)
    {
        if (shell->keyflag->underline && end->under != 1)
            end->under = 1;
        end->s_pos = 0;
        end->prev->s_pos = 1;
        shell->line->last = 0;
        shell->move_cursor = 1;
    }
}

/************************************************************************************
 * FUNCTION MAJ_RIGHT OR MAJ_LEFT
 *
 * ALL VARIABLE			shell->keyflag->underline ===> initialise
 *						shell->mleft ===> is SHIFT + arrow left
 *						shell->mright ==> is SHIFT + arrow right
 *						
 *
 *	Explication : This function is for active underline caractere by caractere
 *				 The last condition IF , for active underline last caractere where is cursor
 *
 * NO NORME
 * *********************************************************************************/

void    ft_move_mleft(t_lineterm *end, t_shell *shell, t_env *env)
{
    if (shell->auto_active || shell->multiauto_active)
        return ;
    shell->keyflag->underline = 1;
    shell->keyflag->mleft = 1;
    shell->keyflag->mright = 0;
    ft_move_left(end, shell, env);
}

void    ft_move_mright(t_lineterm *end, t_shell *shell, t_env *env)
{
    if (shell->auto_active || shell->multiauto_active)
        return ;
    shell->keyflag->underline = 1;
    shell->keyflag->mright = 1;
    shell->keyflag->mleft = 0;
	if (end && end->index == 0)
		end = end->next;
	ft_move_right(end, shell, env);
    if (shell->keyflag->underline && end->under != 1)
		end->under = 1;
}
