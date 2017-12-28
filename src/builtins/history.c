/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 15:07:34 by adebrito          #+#    #+#             */
/*   Updated: 2017/12/20 17:07:19 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"
#include "../../inc/built_in.h"
#include "../../inc/line_edition.h"

static inline void		ft_option_history(char *opt_tab)
{
	opt_tab[0] = '-';
	opt_tab[1] = 'c';
	opt_tab[2] = 'd';
	opt_tab[3] = 'a';
	opt_tab[4] = 'n';
	opt_tab[5] = 'r';
	opt_tab[6] = 'w';
	opt_tab[7] = 'p';
	opt_tab[8] = 's';
	opt_tab[9] = '\0';
}

int						ft_display_history(hlist *histlist)
{
	t_history *begin;

	begin = histlist->begin;
	if (!begin)
		return (1);
	while (begin)
	{
		ft_putnbr(begin->index);
		ft_putchar(' ');
		ft_putendl(begin->data);
		begin = begin->next;
	}
	return (1);
}

int						history(t_cmd *cmd)
{
	t_termc *tsh;
	char    opt[10];

	tsh = ft_ret_tsh(NULL);
	ft_option_history(opt);
	if (cmd->av[1] == NULL)
		return (ft_display_history(tsh->histlist));
	// else
	//     opt = ft_get_option(cmd);
	return (0);
}
