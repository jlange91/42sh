#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"

/************************************************************************************
 * FUNCTION REPLACE CURSOR
 * ALL VARIBLE			last ===> to replace cursor right term
 * 						up ===> up for how time cursor jump
 * 						move_curosr ===> ret how time cursor jump
 * 						and use move_cursor in function ft_del_line
 *
 * 	Explication : This function to place correctly
 *
 * NO NORME
 * **********************************************************************************/
static inline int    ft_cursor_pos(t_lineterm *end, t_termc *shell)
{
    size_t  last;
    int     up;

    if (!end)
        return (-1);
    up = 0;
    last = 0;
    shell->move_cursor = 0;
    while (end->s_pos == 0 && end->index != 0)	
    {
        if (shell->console->char_pos == 0 && end->prev)
        {
            shell->move_cursor++;
            tputs(shell->term->upstr, 1, ft_inputstr);
            shell->console->char_pos = get_columns() - 1;
            last = get_columns() - 1;
            while (last--)
                tputs(shell->term->ndstr, 1, ft_inputstr);
            up++;
        }
        tputs(shell->term->lestr, 1, ft_inputstr);
        shell->console->char_pos--;
        end = end->prev;
    }
    if (shell->keyflag->mright && shell->keyflag->underline)
        tputs(shell->term->lestr, 1, ft_inputstr);
    return (up);
}

/************************************************************************************
 * FUNCTION DEL_LINE
 * ALL VARIABLE				down2 ===> adjust cursor
 * 							down ===> adjust cursor if not key_up or key_down
 *
 * 	Explication : This function catch all line and put correctly
 *
 * NO NORME
 * **********************************************************************************/
static inline void    ft_del_line(t_termc *shell, int down)
{
    size_t  len;
    int     down2;

    len = shell->console->char_pos;
    while (len--)
    {
        tputs(shell->term->lestr, 1, ft_inputstr);
        if (shell->keyflag->backspace == 1)
            tputs(shell->term->dcstr, 1, ft_inputstr);
    }
    while (shell->console->total_line-- > 1)
        tputs(shell->term->upstr, 1, ft_inputstr);
    down2 = down - shell->move_cursor;
    if (down2 == -1)
        while (down2-- > 0)
            tputs(shell->term->dostr, 1, ft_inputstr);
    else if (shell->history->up == 0
            && shell->history->down == 0 && shell->keyflag->cl == 0)
        while (down--) 
            tputs(shell->term->dostr, 1, ft_inputstr);
    if (shell->keyflag->backspace == 1)
        tputs(shell->term->dlstr, 1, ft_inputstr);
}

/************************************************************************************
 * FUNCTION DISPLAY CARACTERE BY CARACTERE
 * ALL VARIABLE			ret ===> the total number from line
 *						col ===> if char_pos == col, we down cursor
 *
 *	Explication : This function display caractere by caractere correctly
 *
 * NO NORME
 * *********************************************************************************/
static void		ft_display_char_split(t_lineterm *begin, t_termc *shell, int *ret)
{
    size_t  	col;

    col = get_columns() - 1;
    if (begin->index == 0 && !shell->quotes)
        ft_putstr(BLUE);
    else
        ft_putstr(RESET);
    if (shell->console->char_pos == col)
    {
        tputs(shell->term->dostr, 1, ft_inputstr);
        shell->console->total_line++;
        shell->console->char_pos = 0;
        *ret = *ret + 1;
    }
    if (begin->under)
        ft_putstr(RED);
    ft_putchar(begin->c);
    shell->console->char_pos++;
    *ret = *ret + shell->console->char_pos;
    ft_putstr(RESET);
}

int    ft_display_char(t_lineterm *begin, t_termc *shell)
{
    int     	ret;

    ret = 0;
    shell->console->char_pos = 0;
    shell->console->total_line = 1;
    while (begin)
    {
        ft_display_char_split(begin ,shell, &ret);
        begin = begin->next;
    }
    if (shell->auto_active || shell->multiauto_active)
        tputs(shell->term->cestr, 1, ft_inputstr);
    else
        tputs(shell->term->cdstr, 1, ft_inputstr);
    shell->history->line_history = shell->console->total_line;
    return (ret);
}

/************************************************************************************
 * FUNCTION ALL_DISPLAY (AFTER CHECK KEY AND INSERT CARACTERE)
 * ALL VARIABLE				close ====> Just reset static int up
 * 						down ====> for function del_line and how time cursor must down
 *						, to adjust good position; he gets from function
 *						ft_cursor_pos;
 *
 *	Explication : DISPLAY LOL ;)
 * NORME OK
 * **********************************************************************************/
int    ft_display(t_termc *shell, int *nbr, int close)
{
    static int  down;
    static int  down2;

    if (close)
    {
        down = 0;
        return (0);
    }
    tputs(shell->term->vistr, 1, ft_inputstr);
    ft_del_line(shell, down);
    *nbr = ft_display_char(shell->line->begin, shell);
    down = ft_cursor_pos(shell->line->end, shell);
    if (shell->auto_active || shell->multiauto_active)
    {
        ft_display_autocompletion(shell, &down2);
        return (down2);
    }
    tputs(shell->term->vestr, 1, ft_inputstr);
    return (down);
}
