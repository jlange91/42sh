/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <stvalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 19:24:14 by stvalett          #+#    #+#             */
/*   Updated: 2017/11/17 08:56:39 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/line_edition.h"

int         ft_inputstr(int c)
{
    write(0, &c, 1);
    return (0);
}

size_t	get_columns(void)
{
    struct winsize	w;

    ioctl(0, TIOCGWINSZ, &w);
    return (w.ws_col);
}

void    ft_free_dlist(dlist **line)
{
    t_lineterm  *del;
    t_lineterm  *elem;

    elem = (*line)->end;
    if (elem != NULL)
    {
        while (elem)
        {
            del = elem;
            elem = elem->prev;
            free(del);
        }
        (*line)->begin = NULL;
        (*line)->end = NULL;
        return ;
    }
}

void    ft_free_autocompletion(t_auto **autocompl)
{
    t_autocompl  *del;
    t_autocompl  *elem;

    elem = (*autocompl)->end;
    if (elem != NULL)
    {
        while (elem)
        {
            del = elem;
            elem = elem->prev;
            free(del->data);
            free(del);
        }
        (*autocompl)->begin = NULL;
        (*autocompl)->end = NULL;
        return ;
    }
}

void    ft_free_all(t_termc *shell)
{
    ft_free_dlist(&shell->line);
	free(shell->line);
	ft_free_dlist(&shell->line_dup);
	free(shell->line_dup);
    free(shell->console);
	free(shell->history);
    ft_free_history(shell->from_hist);
    free(shell->from_hist);
    ft_free_autocompletion(&shell->autocompl);
    if (shell->autocompl->str)
        free(shell->autocompl->str);
    ft_free_autocompletion(&shell->autocompl_binary);
    free(shell->autocompl);
    free(shell->autocompl_binary);
    free(shell->keyflag);
    free(shell->term);
    free(shell);
    shell = NULL;
}

t_lineterm *ft_dont_get_prompt(t_lineterm *tmp)
{
	while (tmp)
	{
        if (tmp->c == '>')
            break;
		tmp = tmp->next;
    }
	tmp = tmp->next;        
	return (tmp);
}
