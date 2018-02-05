/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 19:06:22 by stvalett          #+#    #+#             */
/*   Updated: 2018/01/25 16:05:59 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"

int			ft_init_terminal_mode(t_termc *tsh)
{
	if (tcgetattr(0, &tsh->term->old_termios) == -1)
	{
		ft_putendl_fd("Error, Not save old_term", 2);
		return (1);
	}
	if (tcgetattr(0, &tsh->term->term) == -1)
	{
		ft_putendl_fd("Error, don't get tgetattr", 2);
		return (1);
	}
	tsh->term->term.c_lflag &= ~(ICANON | ECHO);
	tsh->term->term.c_cc[VMIN] = 1;
	tsh->term->term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &tsh->term->term) == -1)
	{
		ft_putendl_fd("Error, don't put tsetattr", 2);
		return (1);
	}
	return (0);
}

int			ft_fill_prompt(t_dlst *line)
{
	char	*str;
	int		i;

	str = NULL;
	str = "21sh $> ";
	if (str)
	{
		i = -1;
		while (str[++i])
			push_backdlst(line, str[i], 0);
		return (1);
	}
	return (0);
}

void		ft_init_console(t_termc *tsh, t_dlst *line)
{
	tsh->console->total_line = 1;
	tsh->console->char_pos = 0;
	if (!tsh->quotes && !tsh->hdoc)
		ft_fill_prompt(line);
	if (!tsh->auto_active && !tsh->multiauto_active)
		ft_init_terminal_mode(tsh);
	if (!tsh->quotes && !tsh->hdoc)
		ft_display_prompt(tsh);
}

void		ft_end_term(t_termc *tsh)
{
	if (tcsetattr(0, TCSANOW, &tsh->term->old_termios) == -1)
	{
		ft_putendl_fd("Error, don't put tsetattr", 2);
		return ;
	}
}
