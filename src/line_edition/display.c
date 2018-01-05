#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"

/************************************************************************************
 * FUNCTION REPLACE CURSOR
 * ALL VARIBLE
 * 						up ===> up for how time cursor jump
 *
 * 	Explication : This function to place correctly
 *
 * NO NORME
 * **********************************************************************************/
static inline int    ft_cursor_pos(t_lineterm *end, t_termc *tsh)
{
	int 	up;

	up = 0;
    if (!end)
        return (-1);
    while (end->s_pos == 0 && end->index != 0)
    {
        if (tsh->console->char_pos == 0 && end->prev)
        {
            tputs(tsh->term->upstr, 1, ft_inputstr);
            tsh->console->char_pos = get_columns() - 1;
			tputs(tparm(tsh->term->ristr, get_columns() -1), 1, ft_inputstr);
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
static inline void    ft_del_line(t_termc *t)
{
	int 	down;

	down = ft_singleton_down(-1);
	while (down-- > 0)
		tputs(t->term->dostr, 1, ft_inputstr);
	t->console->total_line--;
	if (t->console->total_line > 0)
		tputs(tparm(t->term->upstru, t->console->total_line), 1, ft_inputstr);
	tputs(tparm(t->term->lestru, t->console->char_pos), 1, ft_inputstr);
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

/******************************************************************************
 * FUNCTION ALL_DISPLAY (AFTER CHECK KEY AND INSERT CARACTERE)
 * ALL VARIABLE			reset ====> Just reset static int up
 * 						down ====> for function del_line and how time cursor must down
 *						, to adjust good position; he gets from function
 *						ft_cursor_pos;
 *
 *	Explication : DISPLAY LOL ;)
 * NORME OK
 * ****************************************************************************/

int 	ft_singleton_down(int len)
{
	static int  down;

	if (len == 0)
		down = 0;
	else if (len == -1)
		return (down);
	else if (down != len)
		down = len;
	return (down);
}

void    ft_display(t_termc *tsh)
{
	tputs(tsh->term->vistr, 1, ft_inputstr);
    ft_del_line(tsh);
    ft_display_char(tsh->line->begin, tsh);
    ft_singleton_down(ft_cursor_pos(tsh->line->end, tsh));
	if ((tsh->auto_active || tsh->multiauto_active)\
		&& tsh->console->total_line < 2 && !tsh->sigint)
	{
		ft_display_autocompletion(tsh);
		return ;
	}
    tputs(tsh->term->vestr, 1, ft_inputstr);
}
