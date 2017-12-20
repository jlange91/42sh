#include "../../inc/autocompletion.h"


int ft_cursor_update(void)
{
    int         fd, row;

    fd = ft_current_tty();
    if (fd == -1)
        return 1;
    row = 0;
    ft_cursor_position(fd, &row);
    close(fd);
    return (row);
}

int     ft_sk_cursor(int i, int res, t_termc *tsh)
{
    static int ret;

    if (i == 0 && res == 0)
        ret = ft_cursor_update();
    else if (!tsh->autoc->arrow && ret != res)
        ret = ft_cursor_update();
    return (ret);
}

void    ft_display_autocompletion(t_termc *tsh, int *down)
{
    int         i;

	if (tsh->len_prompt >= (int)get_columns())
		return ;
    i = -1;
    tsh->line->last = 1;
    tsh->autoc->jump = 0;
    ft_menu_autocompletion(tsh->autoc, tsh);
    *down = tsh->autoc->jump;
    if (tsh->autoc->clr_yes)
        tputs(tgoto(tgetstr("cm", NULL), 0, tsh->autoc->updaterow - 1),
        1, ft_inputstr);
    tsh->autoc->clr_yes = 0;
}

int    ft_init_value(t_termc *tsh, t_auto *select)
{
    struct winsize  row;

    ioctl(0, TIOCGWINSZ, &row);
    select->max_len = ft_max_len(select);                   //MAX LEN WORD WE CAN FIND
    select->row = row.ws_row - 4;                           //GET_LINE MAX DISPLAY ON SCREEN;
    select->col = (int)((int)(row.ws_col / (select->max_len + 2))); //GET_NUMBER COL
    if (select->col == 0)
        return(0);
    select->jump = (ft_count(select) / select->col) + 1;
    select->pages = tsh->autoc->jump / select->row;   //HOW PAGES DISPLAY
    select->more_pages = tsh->autoc->jump % select->row; //IF REST MORE PAGES
    select->nbr_word = (select->row * select->col); //MAX WORD ON SCREEN
    return (1);
}

int     ft_max_len(t_auto *select)
{
    t_autocompl *begin;
    int         count;

    count = ft_strlen(select->begin->data);
    begin = select->begin->next;
    while (begin)
    {
        if (ft_strlen(begin->data) > count)
            count = ft_strlen(begin->data);
        begin = begin->next;
    }
    return (count);
}

int		ft_count(t_auto *select)
{
    t_autocompl *begin;
    int			count;

    begin = select->begin;
    count = 0;
    while (begin)
    {
        count++;
        begin = begin->next;
    }
    return (count);
}
