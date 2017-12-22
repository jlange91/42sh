#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"

int         ft_inputstr(int c)
{
    write(0, &c, 1);
    return (0);
}

size_t	get_columns(void)
{
    struct winsize	w;

    ioctl(0, TIOCGWINSZ, &w);
    return (w.ws_col);
}

int     ft_reset_line(t_termc *tsh, int ret)
{
    (void)ret;
	ft_display(tsh, 1);
	ft_putchar('\n');
	tsh->autoc->finish = 1;
	tsh->keyflag->cl = 0;
    if (tsh->auto_active || tsh->multiauto_active)
    {
        free(tsh->autoc->str);
        tsh->autoc->str = NULL;
        ft_free_autocompletion(&tsh->autoc);
        tsh->auto_active = 0;
        tsh->multiauto_active = 0;
    }
	tputs(tsh->term->vestr, 1, ft_inputstr);
    return (0);
}

int     ft_save_line(t_termc *tsh)
{
    t_lineterm *tmp;

    tputs(tsh->term->clrstr, 1, ft_inputstr);
    ft_display(tsh, 1);
    tsh->keyflag->cl = 1;
    tmp = tsh->line->begin;
    tmp = ft_dontGetPrompt2(tmp);
    if (tsh->line_dup->begin)
        ft_free_dlist(&tsh->line_dup);
    while (tmp)
    {
        push_backdlst(tsh->line_dup, tmp->c, 1);
        tmp = tmp->next;
    }
    return (0);
}
