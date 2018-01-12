/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 13:16:48 by stvalett          #+#    #+#             */
/*   Updated: 2017/12/19 13:47:51 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"
#include "../../inc/quote.h"

static inline void 	ft_sigwinch(t_termc *tsh)
{
	(void)tsh;
}

static inline void 	ft_sigint2(t_termc *tsh)
{
	int len;

	if (tsh->quotes)
	{
		tsh->quotes = 0;
		ft_skel_quote(NULL, 1);
	}
	if (tsh->hdoc)
		tsh->hdoc = 0;
	ft_free_dlist(&tsh->line);
	len = ft_singleton_down(-1);
	if (len != 0)
		while (len--)
			tputs(tsh->term->dostr, 1, ft_inputstr);
	ft_singleton_down(0);
	ft_init_console(tsh, tsh->line);
	ft_display(tsh);
}

static inline void 	ft_sigint(t_termc *tsh)
{
	tsh->sigint = 1;
	ft_display(tsh);
	if (tsh->auto_active || tsh->multiauto_active)
		tputs(tsh->term->cdstr, 1, ft_inputstr);
	else
		ft_sigint2(tsh);
	ft_init_simple_autocompl(tsh);
	ft_fill_history(tsh);
	tsh->autoc->updaterow = 0;
	tsh->autoc->updaterow = ft_sk_cursor(0, tsh->autoc->updaterow, tsh);
	tsh->autoc->arrow = 0;
	tsh->keyflag->k_tab = 0;
	ft_clean_all_letter(-1, -1);
	tsh->auto_active = 0;
	tsh->multiauto_active = 0;
	tputs(tsh->term->vestr, 1, ft_inputstr);
}

static void				ft_suspended(t_termc *tsh)
{
	char		cp[2];

	ft_end_term(tsh);
	signal(SIGTSTP, SIG_DFL);
	cp[0] = tsh->term->term.c_cc[VSUSP];
	cp[1] = 0;
	ioctl(0, TIOCSTI, cp);
}

void	ft_handle_signal(int signum)
{
	t_termc *tsh;

	tsh = ft_ret_tsh(NULL);
	if (signum == SIGINT)
		ft_sigint(tsh);
	if (signum == SIGWINCH)
		ft_sigwinch(tsh);
	if (signum == SIGCONT)
		ft_init_terminal_mode(tsh);
	if (signum == SIGTSTP)
		ft_suspended(tsh);
}

void 	ft_init_signal(void)
{
	if (signal(SIGINT, ft_handle_signal) == SIG_ERR)
		ft_putstr_fd("\nCan't catch SIGINT\n", 2);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		ft_putstr_fd("\nCan't catch SIGQUIT", 2);
	// if (signal (SIGTSTP, SIG_IGN) == SIG_ERR)
		// ft_putstr_fd("\nCan't catch SIGSTP", 2);
}
