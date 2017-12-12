/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 13:16:48 by stvalett          #+#    #+#             */
/*   Updated: 2017/11/16 12:56:52 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"

extern t_termc *shell_g;

void	ft_handle_signal(int signum)
{

	if (signum == SIGINT)
	{
		int nbr = 0;

		ft_display(shell_g, &nbr, 1);
		while (shell_g->ret_signal-- > 0)
			tputs(shell_g->term->dostr, 1, ft_inputstr);
		shell_g->history->active = 0;										/* FOR PRINT ALL PROMPT */
		ft_free_dlist(&shell_g->line);
		ft_fill_history(shell_g);
		ft_init_console(shell_g, shell_g->line);
        ft_init_simple_autocompl(shell_g);
		ft_display_char(shell_g->line->begin, shell_g);
		shell_g->line->lnk_before = 0;
	}
	else if (signum == SIGWINCH)
	{
		tputs(shell_g->term->clrstr, 1, ft_inputstr);
		ft_display_prompt(shell_g);
		ft_display_char(shell_g->line->begin, shell_g);
	}
    /*else if (signum == SIGTSTP)
    {
        ft_end_term(shell_g);
    }
    else if (signum == SIGCONT)
    {
        ft_free_dlist(&shell_g->line);
		ft_fill_history(shell_g);
		ft_init_console(shell_g, shell_g->line);
        ft_init_simple_autocompl(shell_g, g_env);
		ft_display_char(shell_g->line->begin, shell_g);
		shell_g->line->lnk_before = 0;
    }*/
}

void    ft_handle_signal2(int signum)
{
	if (signum == SIGINT)
	{
		return ;
	}
}

void	ft_catch_sigwinch(int signum)
{
	int nbr;

	if (signum == SIGWINCH)
	{
		nbr = 0;
		tputs(shell_g->term->clrstr, 1, ft_inputstr);
		if (shell_g->len_prompt >= (int)get_columns() - 2)
		{
			ft_putendl_fd("Autocompletion Disabled", 2);
			return ;
		}
        else
            ft_putendl_fd("Autocompletion Enabled", 2);
		ft_display_prompt(shell_g);
		ft_display_char(shell_g->line->begin, shell_g);
		ft_display_autocompletion(shell_g, &nbr);
	}
}
