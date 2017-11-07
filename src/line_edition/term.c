/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 19:24:08 by stvalett          #+#    #+#             */
/*   Updated: 2017/10/27 18:36:59 by stvalett         ###   ########.fr       */
/*   Updated: 2017/10/18 18:46:52 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/line_edition.h"

int		ft_init_terminal_mode(t_shell *shell)
{
    if (tcgetattr(0, &shell->term->old_termios) == -1)
    {
        ft_putendl_fd("Error, Not save old_term", 2);
        return (1);
    }
    if (tcgetattr(0, &shell->term->term) == -1)
    {
        ft_putendl_fd("Error, don't get tgetattr", 2);
        return (1);
    }
    shell->term->term.c_lflag &= ~(ICANON | ECHO);
    shell->term->term.c_cc[VMIN] = 1;
    shell->term->term.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &shell->term->term) == -1)
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
            ft_fill_back_dlst(line, str[i], 0);
        free(str);
        return (1);
    }
    return (0);
}

static inline void	ft_init_console_split(t_shell *shell)
{
    int	            i;
    size_t          res;
    size_t          col;

    res = 0;
    col = get_columns() - 1;
    i = -1;
    while (++i < (int)col)
    {
        tputs(shell->term->lestr, 1, ft_inputstr);
        if (shell->keyflag->backspace)
            tputs(shell->term->dcstr, 1, ft_inputstr);
    }
    res = shell->history->line_history;
    res = res - shell->move_cursor;
    while (res > 1)
    {
        tputs(shell->term->upstr, 1, ft_inputstr);
        res--;
    }
    tputs(shell->term->cdstr, 1, ft_inputstr);
}

void    ft_init_console(t_shell *shell, dlist *line, t_env *env)
{
    shell->console->total_line = 1;
    shell->console->line_pos = 1;
    shell->console->char_pos = 0;
    ft_fill_prompt(line);
    if (shell->history->active)
    {
        ft_init_console_split(shell);
        return ;
    }
    if (!shell->auto_active && !shell->multiauto_active)
        ft_init_terminal_mode(shell);
    ft_display_prompt(shell, env);
}

void    ft_end_term(t_shell *shell)
{
    if (tcsetattr(0, TCSANOW, &shell->term->old_termios) == -1)
    {
        ft_putendl_fd("Error, don't put tsetattr", 2);
        exit(1);
    }
}
