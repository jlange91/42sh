#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"

int     ft_reset_line(t_shell *shell, int ret, t_env *env)
{
    int nbr;

    nbr = 0;
    if (shell->auto_active || shell->multiauto_active)
    {
        tputs(shell->term->dostr, 1, ft_inputstr);
        free(shell->autocompl->str);
        shell->autocompl->str = NULL;
        ft_free_autocompletion(&shell->autocompl);
        shell->auto_active = 0;
        shell->multiauto_active = 0;
    }
    shell->autocompl->finish = 1;
    ft_display(shell, &nbr, 1, env);
    while (ret--)
        tputs(shell->term->dostr, 1, ft_inputstr);
	shell->keyflag->cl = 0;
    return (0);
}
