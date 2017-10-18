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

void    ft_display_autocompletion(t_shell *shell, int *down)
{
    int         total;
    int         i;

	if (shell->len_prompt >= (int)get_columns())
		return ;
    i = -1;
    total = 0;
    shell->line->last = 1;
    shell->autocompl->jump = 0;
    ft_menu_autocompletion(shell->autocompl, shell, &total);
    *down = shell->autocompl->jump;
    if (shell->autocompl->clr_yes)
        tputs(tgoto(tgetstr("cm", NULL), 0, shell->autocompl->updaterow - 1), 1, ft_inputstr);
    while (total--)
        tputs(shell->term->lestr, 1, ft_inputstr);
    while (++i < ft_count_dlnk(shell) + 8)
        tputs(shell->term->ndstr, 1, ft_inputstr);
    shell->autocompl->clr_yes = 0;
    tputs(shell->term->vestr, 1, ft_inputstr);
}

int    ft_init_value(t_shell *shell, t_auto *select)
{
    struct winsize  row;

    ioctl(0, TIOCGWINSZ, &row);
    select->max_len = ft_max_len(select);                   //MAX LEN WORD WE CAN FIND
    select->row = row.ws_row - 4;                           //GET_LINE MAX DISPLAY ON SCREEN;
    select->col = ((row.ws_col / select->max_len) - 1); //GET_NUMBER COL
    if (select->col == 0)
    {
        return(0);
    }
    select->jump = (ft_count(select) / select->col) + 1;
    select->pages = shell->autocompl->jump / select->row;   //HOW PAGES DISPLAY
    select->more_pages = shell->autocompl->jump % select->row; //IF REST MORE PAGES
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
        if (ft_strlen(begin->data) > (size_t)count)
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
