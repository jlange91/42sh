/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebrito <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 12:46:04 by adebrito          #+#    #+#             */
/*   Updated: 2017/11/22 13:31:28 by adebrito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int		ft_find_term_db(char *term_name)
{
	int result;

	result = tgetent(0, term_name);
	if (result == 0 || result == -1)
	{
		if (result == 0)
		{
			ft_putstr(term_name);
			ft_putstr("not found in the termcap DB\n");
		}
		else
			ft_putstr("Could not access to the termcap DB\n");
		return (-1);
	}
	return (0);
}

static	int		ft_modif_term(t_select **select)
{
	struct termios	term;
	t_select		*s;

	s = *select;
	if (tcgetattr(0, &term) == -1)
	{
		ft_putstr("Error cannot fill up the term struct\n");
		return (-1);
	}
	s->default_term = term;
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
	{
		ft_putstr("Cannot apply the change, on the term struct\n");
		return (-1);
	}
	tputs(tgetstr("ti", NULL), 0, ft_putc);
	tputs(tgetstr("vi", NULL), 0, ft_putc);
	return (0);
}

int				ft_find_window_len(t_select **select)
{
	struct winsize	w;
	t_select		*s;
	int				col;

	s = *select;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	s->width = w.ws_col;
	s->height = w.ws_row;
	col = s->nb_elem / s->height;
	if (s->max_strlen > s->width - 10)
		return (0);
	return ((col * s->max_strlen + 5) < s->width);
}

void			ft_init_term(t_select **select)
{
	char	*term_name;

	term_name = getenv("TERM");
	if (term_name == 0 || ft_find_term_db(term_name) == -1)
	{
		if (term_name == 0)
			ft_putstr("TERM is undefined in env\n");
		exit(EXIT_FAILURE);
	}
	if (ft_modif_term(select) == -1)
	{
		exit(EXIT_FAILURE);
		ft_find_window_len(select);
	}
}
