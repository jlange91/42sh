#include "../../inc/autocompletion.h"
#include "../../inc/line_edition.h"

static void    ft_display_autocompl(t_autocompl *begin, t_auto *select)
{
    struct stat info_data;
    struct stat info_str;
    char        *tmp;

    ft_memset(&info_data, 0, sizeof(info_data));
    stat(begin->data, &info_data);
    ft_memset(&info_str, 0, sizeof(info_str));
    tmp = ft_strjoin(select->str, begin->data);
    stat(tmp, &info_str);
    if (begin == select->current && select->can_print >= 1)
    {
        ft_putstr(ORANGE_FRONT);
        ft_putstr(PURPLE_BACK);
        //tputs(shell->term->usstr, 1, ft_inputstr);
        ft_putstr(begin->data);
        //tputs(shell->term->uestr, 1, ft_inputstr);
        ft_putstr(RESET);
        if (S_ISDIR(info_data.st_mode))
            ft_putchar('/');
        else if (S_ISDIR(info_str.st_mode))
            ft_putchar('/');
    }
    else
    {
        if (S_ISDIR(info_data.st_mode))
        {
            ft_putstr(BLUE);
            ft_putstr(begin->data);
            ft_putchar('/');
        }
        else if (S_ISDIR(info_str.st_mode))
        {
            ft_putstr(BLUE);
            ft_putstr(begin->data);
            ft_putchar('/');
        }
        else if ((S_ISREG(info_data.st_mode)) && (info_data.st_mode & 0001))
        {
            ft_putstr(RED);
            ft_putstr(begin->data);
            ft_putchar('*');
        }
        else if ((S_ISREG(info_str.st_mode)) && (info_str.st_mode & 0001))
        {
            ft_putstr(RED);
            ft_putstr(begin->data);
            ft_putchar('*');
        }
        else
            ft_putstr(begin->data);
        ft_putstr(RESET);
    }
    free(tmp);
}

static t_var_auto      *ft_init_var(t_auto *select)
{
    t_var_auto  *var;

    var = NULL;
    if ((var = (t_var_auto *)malloc(sizeof(*var))) == NULL)
    {
        ft_putendl_fd("Error malloc", 2);
        return (NULL);
    }
    var->len = 0;
    var->down = 0;
    var->row = select->updaterow - 1;
    var->ttl_jump = select->jump + 1;
    return (var);
}

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

    var = ft_init_var(select);
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

static int ft_print_full_screen(t_auto *select, t_var_auto *var, t_autocompl *begin, int limit_word)
{
    while (begin && begin->index <= limit_word)
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
        var = ft_init_var(select);
        limit_word = select->jump * select->col * nbr;
        total = ft_print_full_screen(select, var, begin, limit_word);
        free(var);
        select->clr_yes = 1;
        return (total);
    }
    else
        return (ft_print_simple_auto(select, begin));
}

void ft_menu_autocompletion(t_auto *select, t_shell *shell, int *total, t_env *env)
{
    t_autocompl *begin;
    static int count;

    begin = select->begin;
    if (begin)
    {
        ft_init_value(shell, select);
        if (shell->autocompl->jump > select->row)
            ft_multi_pages(select, shell, begin, total, env);
        else
        {
            if (!shell->autocompl->arrow && count++ < 1)
            {
                shell->autocompl->updaterow = ft_cursor_update();
                count = 0;
            }
            *total = ft_diff_print(select, begin, 0, 1);
        }
        select->arrow = 0;
    }
}
