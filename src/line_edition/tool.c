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

void 	ft_clean_line(t_termc *tsh)
{
	t_lineterm *end;
	t_lineterm *del;

	end = tsh->line->end;
	while (end)
	{
		if (end->index == 0)
			break ;
		del = end;
		if (end->next == NULL)
		{
			tsh->line->end = end->prev;
			tsh->line->end->next = NULL;
		}
		else if (end->prev == NULL)
		{
			tsh->line->begin = end->next;
			tsh->line->begin->prev = NULL;
		}
		else
		{
			end->prev->next = end->next;
			end->next->prev = end->prev;
		}
		end = end->prev;
		free(del);
	}
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

void    ft_free_autocompletion(t_auto **autoc)
{
    t_autocompl  *del;
    t_autocompl  *elem;

    elem = (*autoc)->end;
    if (elem != NULL)
    {
        while (elem)
        {
            del = elem;
            elem = elem->prev;
            free(del->data);
            free(del);
        }
        (*autoc)->begin = NULL;
        (*autoc)->end = NULL;
        return ;
    }
}

void    ft_free_all(t_termc *tsh)
{
    ft_free_dlist(&tsh->line);
	free(tsh->line);
	ft_free_dlist(&tsh->line_dup);
	free(tsh->line_dup);
    free(tsh->console);
	free(tsh->history);
    ft_free_history(tsh->histfile);
    free(tsh->histfile->pwd);
    free(tsh->histfile);
    if (tsh->autoc->str)
        free(tsh->autoc->str);
    ft_free_autocompletion(&tsh->autoc);
    free(tsh->autoc);
    free(tsh->keyflag);
    free(tsh->term);
    free(tsh);
    tsh = NULL;
}

t_lineterm *ft_dontGetPrompt2(t_lineterm *tmp)
{
	int	i;

	i = 0;
	while (tmp)
	{
        if (i > 7)
            break;
		i++;
		tmp = tmp->next;
    }
	return (tmp);
}
