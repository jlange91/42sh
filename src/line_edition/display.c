#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"

/************************************************************************************
 * FUNCTION REPLACE CURSOR
 * ALL VARIBLE			last ===> to replace cursor right term
 * 						up ===> up for how time cursor jump
 *
 * 	Explication : This function to place correctly
 *
 * NO NORME
 * **********************************************************************************/
static inline int    ft_cursor_pos(t_lineterm *end, t_termc *tsh, int up)
{
    size_t  last;

    if (!end)
        return (-1);
    while (end->s_pos == 0 && end->index != 0)
    {
        if (tsh->console->char_pos == 0 && end->prev)
        {
            tputs(tsh->term->upstr, 1, ft_inputstr);
            tsh->console->char_pos = get_columns() - 1;
            last = get_columns() - 1;
            while (last--)
                tputs(tsh->term->ndstr, 1, ft_inputstr);
            up++;
        }
        tputs(tsh->term->lestr, 1, ft_inputstr);
        tsh->console->char_pos--;
        end = end->prev;
    }
    if (tsh->keyflag->mright && tsh->keyflag->underline
            && end->prev->index != 0)
        tputs(tsh->term->lestr, 1, ft_inputstr);
    return (up);
}

/************************************************************************************
 * FUNCTION DEL_LINE
 * ALL VARIABLE
 * 							down ===> adjust cursor if not key_up or key_down
 *
 * 	Explication : This function catch all line and put correctly
 *
 * NO NORME
 * **********************************************************************************/
static inline void    ft_del_line(t_termc *tsh, int down)
{
    size_t  len;

    len = tsh->console->char_pos;
    while (down--)
        tputs(tsh->term->dostr, 1, ft_inputstr);
    while (tsh->console->total_line-- > 1)
        tputs(tsh->term->upstr, 1, ft_inputstr);
    while (len--)
        tputs(tsh->term->lestr, 1, ft_inputstr);
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
static void		ft_display_char_split(t_lineterm *begin, t_termc *tsh)
{
    size_t  	col;

    col = get_columns() - 1;
    if (begin->index == 0 && !tsh->quotes)
        ft_putstr(BLUE);
    else
        ft_putstr(RESET);
    if (tsh->console->char_pos == col)
    {
        tputs(tsh->term->dostr, 1, ft_inputstr);
        tsh->console->total_line++;
        tsh->console->char_pos = 0;
    }
    if (begin->under)
        ft_putstr(RED);
    if (begin->c != '\t')
        ft_putchar(begin->c);
    tsh->console->char_pos++;
    ft_putstr(RESET);
}

int    ft_display_char(t_lineterm *begin, t_termc *tsh)
{
    tsh->console->char_pos = 0;
    tsh->console->total_line = 1;
    while (begin)
    {
        ft_display_char_split(begin ,tsh);
        begin = begin->next;
    }
    if (tsh->auto_active || tsh->multiauto_active)
        tputs(tsh->term->cestr, 1, ft_inputstr);
    else
        tputs(tsh->term->cdstr, 1, ft_inputstr);
    return (0);
}

/************************************************************************************
 * FUNCTION ALL_DISPLAY (AFTER CHECK KEY AND INSERT CARACTERE)
 * ALL VARIABLE			reset ====> Just reset static int up
 * 						down ====> for function del_line and how time cursor must down
 *						, to adjust good position; he gets from function
 *						ft_cursor_pos;
 *
 *	Explication : DISPLAY LOL ;)
 * NORME OK
 * **********************************************************************************/
int    ft_display(t_termc *tsh, int reset)
{
    static int  down;
    static int  down2;
    int         up;

    if (reset)
    {
        down = 0;
        return (0);
    }
    tputs(tsh->term->vistr, 1, ft_inputstr);
    ft_del_line(tsh, down);
    up = 0;
    ft_display_char(tsh->line->begin, tsh);
    down = ft_cursor_pos(tsh->line->end, tsh, up);
    if (tsh->auto_active || tsh->multiauto_active)
    {
        ft_display_autocompletion(tsh, &down2);
        return (down2);
    }
    tputs(tsh->term->vestr, 1, ft_inputstr);
    return (down);
}
