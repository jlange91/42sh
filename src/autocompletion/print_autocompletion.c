#include "../../inc/autocompletion.h"
#include "../../inc/line_edition.h"

static void     ft_check_line_simple(t_auto *select, t_var_auto *var)
{
    if (var->ttl_jump > 0)
    {
        ft_putchar('\n');
        if (var->row++ >= select->row + 4)
            var->down++;
        var->ttl_jump--;
    }
    if (var->ttl_jump == 0)
    {
        if (var->len + select->max_len + 2 < (int)get_columns())
            var->len += select->max_len + 2;
        var->ttl_jump = select->jump;
        if (var->down != 0)
            var->row = select->updaterow - (var->down + 1);
        else
            var->row = select->updaterow;
        if (var->row - 2 == select->row && select->jump != 1)              //SI ON 3 LIGNE AVANT LA FIN PRENANT EN COMPTE LE PROMPT
        {
            select->updaterow--;
            var->row--;
        }
    }
    tputs(tgoto(tgetstr("cm", NULL), var->len, var->row), 1, ft_inputstr);
}

static int      ft_print_simple_auto(t_auto *select, t_autocompl *begin)
{
    t_var_auto  *var;
    int total;

    var = ft_init_var_auto(select);
    while (begin)
    {
        ft_check_line_simple(select, var);
        ft_display_autocompl(begin, select);
        begin = begin->next;
    }
    if (var->down != 0)
        select->updaterow = select->updaterow - (var->down + 1);
    select->clr_yes = 1;
    total = var->len;
    free(var);
    return (total);
}

static int ft_pfsc(t_auto *select, t_var_auto *var, t_autocompl *begin, int l_w)
{
    while (begin && begin->index <= l_w)
    {
        if (var->ttl_jump > 0)
        {
            ft_putchar('\n');
            var->row++;
            var->ttl_jump--;
        }
        if (var->ttl_jump == 0)
        {
            if (var->len + select->max_len + 2 < (int)get_columns() - 1)
                var->len += select->max_len + 2;
            var->ttl_jump = select->jump;
            var->row = select->updaterow;
        }
        tputs(tgoto(tgetstr("cm", NULL), var->len, var->row), 1, ft_inputstr);
        ft_display_autocompl(begin, select);
        begin = begin->next;
    }
    return (var->len);
}

int    ft_diff_print(t_auto *select, t_autocompl *begin, int nbr, int flag)
{
    t_var_auto  *var;

    int         limit_word;
    int         total;

    if (flag == 2)
    {
        var = ft_init_var_auto(select);
        limit_word = select->jump * select->col * nbr;
        total = ft_pfsc(select, var, begin, limit_word);
        free(var);
        select->clr_yes = 1;
        return (total);
    }
    else
        return (ft_print_simple_auto(select, begin));
}

void ft_menu_autocompletion(t_auto *select, t_termc *tsh, int *total)
{
    t_autocompl *begin;
    static int count;

    begin = select->begin;
    if (begin)
    {
        ft_init_value(tsh, select);
        if (tsh->autoc->jump > select->row)
            ft_mpages(select, tsh, begin, total);
        else
        {
            if (!tsh->autoc->arrow && count++ < 1)
            {
                tsh->autoc->updaterow = ft_cursor_update();
                count = 0;
            }
            *total = ft_diff_print(select, begin, 0, 1);
        }
        select->arrow = 0;
    }
}
