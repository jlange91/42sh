/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 15:24:13 by vmartins          #+#    #+#             */
/*   Updated: 2018/01/25 11:25:43 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/line_edition.h"

void			ft_free_t_dlst(t_dlst **line)
{
	t_lineterm	*del;
	t_lineterm	*elem;

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

void			ft_free_autocompletion(t_auto **autoc)
{
	t_autocompl	*del;
	t_autocompl	*elem;

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

void			ft_free_all(t_termc *tsh)
{
	ft_free_t_dlst(&tsh->line);
	free(tsh->line);
	ft_free_t_dlst(&tsh->line_dup);
	free(tsh->line_dup);
	free(tsh->console);
	free(tsh->histmp);
	ft_free_history(tsh->histlist);
	free(tsh->histlist->pwd);
	free(tsh->histlist);
	if (tsh->autoc->str)
		free(tsh->autoc->str);
	ft_free_autocompletion(&tsh->autoc);
	free(tsh->autoc);
	free(tsh->keyflag);
	free(tsh->term);
	free(tsh);
	tsh = NULL;
}
