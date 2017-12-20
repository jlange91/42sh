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

void 	ft_sigint(t_termc *tsh)
{
	ft_display(tsh, 1);
	if (!(tsh->auto_active) && (!(tsh->multiauto_active)))
	{
		while (tsh->ret_signal-- > 0)
			tputs(tsh->term->dostr, 1, ft_inputstr);
		ft_free_dlist(&tsh->line);
		ft_init_console(tsh, tsh->line);
	}
	else
		tputs(tsh->term->cdstr, 1, ft_inputstr);
	ft_display_char(tsh->line->begin, tsh);
	tsh->autoc->updaterow = 0;
	tsh->autoc->updaterow = ft_sk_cursor(0, tsh->autoc->updaterow, tsh);
	tsh->autoc->arrow = 0;
	tsh->key_tab = 0;
	ft_clean_all_letter(-1, -1);
	tsh->auto_active = 0;
	tsh->multiauto_active = 0;
	tputs(tsh->term->vestr, 1, ft_inputstr);
}

void	ft_handle_signal(int signum)
{
	t_termc *tsh;

	tsh = ft_ret_tsh(NULL);
	if (signum == SIGINT)
		ft_sigint(tsh);
}
