/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebrito <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 14:40:50 by adebrito          #+#    #+#             */
/*   Updated: 2017/12/18 16:44:17 by adebrito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static int		init_elem(t_select **select, char **av, int ac)
{
	t_select	*s;
	t_elem		*elem;
	int			i;
	int			len;

	s = *select;
	i = -1;
	if (!(elem = (t_elem *)malloc(sizeof(t_elem) * ac)))
		return (0);
	elem[ac - 1].str = NULL;
	while (av[++i])
	{
		if ((len = ft_strlen(av[i])) > s->max_strlen)
			s->max_strlen = len;
		elem[i].str = ft_strdup(av[i]);
		elem[i].select = 0;
	}
	s->elem = elem;
	return (0);
}

int				main(int ac, char **av, char **env)
{
	t_select	*s;
	char			*str;

	(void)ac;
	str = "COPIER/COLLER COUPER/COLLER SE_DEPLACER SELECTION AUTOCOMPLETION \
GLOBBING HISTORIQUE";
	av = ft_strsplit(str, ' ');
	if (!(s = (t_select *)malloc(sizeof(t_select))))
		return (0);
	s->nb_elem = ft_tablen(av);
	s->cursor_line = 1;
	s->max_strlen = 0;
	if (ft_tablen(av) > 1)
	{
		s->env = ft_tabdup(env);
		init_elem(&s, av, ft_tablen(av));
		keep_term(s);
		ft_signal(av);
		ft_select(&s);
	}
	return (0);
}
