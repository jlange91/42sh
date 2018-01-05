/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 19:24:08 by stvalett          #+#    #+#             */
/*   Updated: 2017/11/16 12:14:13 by stvalett         ###   ########.fr       */
/*   Updated: 2017/10/18 18:46:52 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"

int		ft_init_terminal_mode(t_termc *tsh)
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

int		ft_fill_prompt(dlist *line)
{
    char	*str;
    int		i;

    str = NULL;
    str = ft_strdup("42sh $> ");
    if (str)
    {
        i = -1;
        while (str[++i])
            push_backdlst(line, str[i], 0);
        free(str);
        return (1);
    }
    return (0);
}

void    ft_init_console(t_termc *tsh, dlist *line)
{
	tsh->console->total_line = 1;
	tsh->console->char_pos = 0;
    ft_fill_prompt(line);
    if (!tsh->auto_active && !tsh->multiauto_active)
        ft_init_terminal_mode(tsh);
	ft_display_prompt(tsh);
}

void    ft_end_term(t_termc *tsh)
{
    if (tcsetattr(0, TCSANOW, &tsh->term->old_termios) == -1)
    {
        ft_putendl_fd("Error, don't put tsetattr", 2);
        exit(1);
    }
}
