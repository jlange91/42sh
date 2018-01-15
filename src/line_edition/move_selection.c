#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"

/************************************************************************************
 * FUNCTION MOVE_RIGHT OR MOVE_LEFT
 *
 * ALL VARIABLE
 *						tsh->end->s_pos ===> If cursor can be here or not
 *												if s_pos == 0 , cursor can be on the letter else can't
 *						tsh->end->under ==> active underline caractere if keyflag->underline is active
 *						tsh->line->last ==> if we are end of the double linked , we active this variable
 *												else we active tsh->line->lnk_before
 *
 *
 *	Explication : This function display caractere by caractere correctly
 *
 * NO NORME
 * *********************************************************************************/

void	ft_move_right(t_lineterm *end, t_termc *tsh)
{
    if (tsh->auto_active || tsh->multiauto_active)
    {
		if (tsh->console->total_line > 1)
			return ;
        ft_autoMove(end, tsh, 1);
        return ;
    }
    tsh->auto_active = 0;
    tsh->multiauto_active = 0;
    if (end && end->next)
    {
        if (tsh->keyflag->underline && end->next->under != 1)
            end->next->under = 1;
        end->s_pos = 0;
        end->next->s_pos = 1;
        if (!end->next->next)
            tsh->line->last = 1;
        else
            tsh->line->lnk_before = 1;
    }
}

void    ft_move_left(t_lineterm *end, t_termc *tsh)
{
    if (tsh->auto_active || tsh->multiauto_active)
    {
		if (tsh->console->total_line > 1)
			return ;
        ft_autoMove(end, tsh, 0);
        return ;
    }
    tsh->auto_active = 0;
    tsh->multiauto_active = 0;
    if (end->prev && end->index != 0)
    {
        if (tsh->keyflag->underline && end->under != 1)
            end->under = 1;
        end->s_pos = 0;
        end->prev->s_pos = 1;
        tsh->line->last = 0;
    }
}

/************************************************************************************
 * FUNCTION MAJ_RIGHT OR MAJ_LEFT
 *
 * ALL VARIABLE
 *						tsh->mleft ===> is SHIFT + arrow left
 *						tsh->mright ==> is SHIFT + arrow right
 *
 *
 *	Explication : This function is for active underline caractere by caractere
 *				 The last condition IF , for active underline last caractere where is cursor
 *
 * NO NORME
 * *********************************************************************************/

void    ft_move_mleft(t_lineterm *end, t_termc *tsh)
{
    if (tsh->auto_active || tsh->multiauto_active)
        return ;
    tsh->keyflag->underline = 1;
    ft_move_left(end, tsh);
}

void    ft_move_mright(t_lineterm *end, t_termc *tsh)
{
    if (tsh->auto_active || tsh->multiauto_active)
        return ;
    tsh->keyflag->underline = 1;
    ft_move_right(end, tsh);
}
