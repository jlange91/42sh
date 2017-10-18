#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"

static void    ft_init_tab_key(long keycode[15])
{
    keycode[0] = RIGHT;
    keycode[1] = LEFT;
    keycode[2] = MAJ_RIGHT;
    keycode[3] = MAJ_LEFT;
    keycode[4] = HOME;
    keycode[5] = END;
    keycode[6] = OPT_F;
    keycode[7] = OPT_B;
    keycode[8] = OPT_C;
    keycode[9] = OPT_P;
    keycode[10] = OPT_X;
    keycode[11] = OPT_UP;
    keycode[12] = OPT_DOWN;
    keycode[13] = TAB;
}

static void    ft_init_tab_funct(t_k funct[15])
{
    funct[0] = ft_move_right;
    funct[1] = ft_move_left;
    funct[2] = ft_move_mright;
    funct[3] = ft_move_mleft;
    funct[4] = ft_move_begin;
    funct[5] = ft_move_end;
    funct[6] = ft_move_word_forward;
    funct[7] = ft_move_word_back;
    funct[8] = ft_dup_line;
    funct[9] = ft_past_line;
    funct[10] = ft_cut_line;
    funct[11] = ft_move_up_line;
    funct[12] = ft_move_down_line;
    funct[13] = ft_autocompletion;
}

int     ft_dynamique_autocompletion(long *c, t_shell *shell, t_env *env)
{
    static int compt;
    (void)env;

    if (shell->count_tab && (shell->auto_active || shell->multiauto_active) && *c == TAB)
    {
        compt++;
        *c = RIGHT;
    }
    if (*c == '\n' && (shell->auto_active || shell->multiauto_active))
    {
        shell->count_tab = 0;
        if (compt < 1)
        {
            shell->auto_active = 0;
            shell->multiauto_active = 0;
            return (0);
        }
        *c = TAB;
        compt = 0;
    }
    return (1);
}

int     ft_other_key(t_lineterm *end, t_shell *shell, long c, t_env *env)
{
    int     i;
    static long    keycode[15];
    static t_k		funct[15];
    static int count;

    if (count++ < 1)
    {
        ft_init_tab_key(keycode);
        ft_init_tab_funct(funct);
    }
    i = -1;
    if (!ft_dynamique_autocompletion(&c, shell, env))
        return (0);
    while (++i < 14)
        if (keycode[i] == c)
        {
            funct[i](end, shell, env);
            return (1);
        }
    return (0);
}
