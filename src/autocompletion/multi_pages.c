#include "../../inc/autocompletion.h"

static int    ft_print_page(t_termc *tsh, t_auto *select, t_autocompl *begin)
{
    int         i;
    int         total;

    i = 0;
    total = 0;
    while (++i <= select->pages)
    {
        tsh->autoc->jump = select->row;
        if (select->nbr_word >= select->current->index)
        {
            total = ft_diff_print(select, begin, i, 2);
            break;
        }
        else if (select->nbr_word * (i + 1) >= select->current->index
                && select->pages > 1
                && select->nbr_word * select->pages >= select->current->index)
        {
            while (begin && begin->index < select->nbr_word * i)
                begin = begin->next;
            begin = begin->next;
            total = ft_diff_print(select, begin, i + 1, 2);
            break;
        }
    }
    return (total);
}

static void    what_pages(t_termc *tsh, t_auto *select, int *ecrase, int *e_s)
{
    int         i;

    i = 0;
    while (++i <= select->pages)
    {
        tsh->autoc->jump = select->row;
        if (select->nbr_word >= select->current->index)
        {
            *ecrase = i;
            *e_s = 0;
            break;
        }
        else if (select->nbr_word * (i + 1) >= select->current->index
                && select->pages > 1
                && select->nbr_word * select->pages >= select->current->index)
        {
            *ecrase = i + 1;
            *e_s = 0;
            break;
        }
    }
}


static void ft_clean_screen(t_auto *select, t_termc *tsh, int *ecrase, int *e_s)
{
    int         row;

    tputs(tgoto(tgetstr("cm", NULL), 0, select->row + 4), 1, ft_inputstr);
    row = select->row + 4;
    while (row--)
        tputs(tgetstr("up", NULL), 1, ft_inputstr);
    what_pages(tsh, select, ecrase, e_s);
}

void    ft_mpages(t_auto *select, t_termc *tsh, t_autocompl *begin, int *total)
{
    static int ret;
    static int ecrase;
    static int ecrase_simple;

    ft_clean_screen(select, tsh, &ecrase, &ecrase_simple);
    if (ret != ecrase)
    {
        tputs(tgetstr("cd", NULL), 1, ft_inputstr);
        ret = ecrase;
    }
    ft_display_prompt(tsh);
    ft_display_char(tsh->line->begin, tsh);
    tsh->autoc->updaterow = 3;
    *total = ft_print_page(tsh, select, begin);
    if (select->more_pages != 0
            && select->current->index > select->nbr_word * select->pages)
    {
        ret = -1;
        if (ecrase_simple++ < 1)
            tputs(tgetstr("cd", NULL), 1, ft_inputstr);
        tsh->autoc->jump = select->more_pages;
        while (begin && begin->index <= select->nbr_word * select->pages)
            begin = begin->next;
        *total = ft_diff_print(select, begin, 0, 1);
    }
}
