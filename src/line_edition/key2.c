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
	keycode[9] = OPT_V;
	keycode[10] = OPT_X;
	keycode[11] = OPT_UP;
	keycode[12] = OPT_DOWN;
	keycode[13] = NO_PRINT;
	keycode[14] = TAB;
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
	funct[13] = ft_move_down_line_auto;
	funct[14] = ft_autocompletion;
}

int     ft_dynamique_autocompletion(long *c, t_termc *tsh)
{
	static int compt;

	if (tsh->keyflag->k_tab &&
			(tsh->auto_active || tsh->multiauto_active)&& *c == TAB)
	{
		compt++;
		*c = NO_PRINT;
		tsh->autoc->can_print++;
	}
	if (*c == '\n' && (tsh->auto_active || tsh->multiauto_active))
	{
		tsh->autoc->can_print = 14;
		tsh->keyflag->k_tab = 0;
		if (compt < 1)
		{
			tsh->auto_active = 0;
			tsh->multiauto_active = 0;
			return (0);
		}
		*c = TAB;
		compt = 0;
	}
	return (1);
}

static int  ft_exec_key(t_termc *tsh, long c, t_lineterm *end)
{
	int     		i;
	static int 		count;
	static long    	keycode[15];
	static t_k		funct[15];

	if (count++ < 1)
	{
		ft_init_tab_key(keycode);
		ft_init_tab_funct(funct);
	}
	i = -1;
	while (++i < 15)
		if (keycode[i] == c)
		{
			if ((tsh->quotes || tsh->hdoc) && i > 1)
				return (1);
			else if (tsh->autoc->can_print < 2 && i == 13)
				return (1);
			funct[i](end, tsh);
			return (1);
		}
	return (0);
}

int     ft_other_key(t_lineterm *end, t_termc *tsh, long c)
{
	if (!ft_dynamique_autocompletion(&c, tsh))
		return (0);
	if (tsh->autoc->can_print < 2 && c == NO_PRINT)
	{
		ft_clean_line(tsh);
		ft_cpy_autocompl_to_lineshell(tsh);
	}
	return (ft_exec_key(tsh, c, end));
}
