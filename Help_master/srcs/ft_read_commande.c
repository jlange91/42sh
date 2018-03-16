/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_commande.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 10:57:45 by vmartins          #+#    #+#             */
/*   Updated: 2018/01/24 16:05:28 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void				ft_escape(t_select **select, char **content)
{
	t_select	*s;
	char		*cap;

	s = *select;
	if ((cap = tgetstr("rc", NULL)) == NULL)
		ft_putendl("Cannot restor the cursor position");
	else
		tputs(cap, 0, ft_putc);
	if ((cap = tgetstr("cd", NULL)) == NULL)
		ft_putendl("Cannot delete line below the cursor position");
	else
		tputs(cap, 0, ft_putc);
	ft_putchar('\n');
	tputs(tgetstr("te", NULL), 0, ft_putc);
	tputs(tgetstr("ve", NULL), 0, ft_putc);
	s->default_term.c_lflag |= ICANON;
	s->default_term.c_lflag |= ECHO;
	tcsetattr(0, 0, &(s->default_term));
	if (content)
	{
		ft_putab_inline(content);
		ft_putchar('\n');
		free_tab((void**)content, ft_tablen(content));
	}
	exit(0);
}

void				ft_read_commande(t_select **select)
{
	t_select	*s;
	char		buf[4];
	char		*cap;

	s = *select;
	cap = NULL;
	while (42)
	{
		ft_bzero(buf, 2);
		read(0, buf, 3);
		if (ft_strcmp(buf, "\n") == 0)
			ft_valide_select(select);
		else if (buf[0] == 27 && ft_strlen(buf) == 3)
			ft_arrow_key(select, buf);
		else if (buf[0] == 27 && ft_strlen(buf) == 1)
			ft_escape(select, NULL);
	}
}
