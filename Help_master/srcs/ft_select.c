/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 09:30:47 by vmartins          #+#    #+#             */
/*   Updated: 2017/11/22 13:31:13 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		ft_select(t_select **select)
{
	t_select		*s;
	char			*cap;

	s = *select;
	ft_init_term(select);
	if ((cap = tgetstr("sc", NULL)) == NULL)
		ft_putstr("Cannot save cursor position\n");
	else
		tputs(cap, 0, ft_putc);
	if ((cap = tgetstr("RA", NULL)) == NULL)
		ft_putstr("Cannot disabled margin auto\n");
	else
		tputs(cap, 0, ft_putc);
	ft_print_all(select, 0, 0);
	ft_read_commande(select);
}
