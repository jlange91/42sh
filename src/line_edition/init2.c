/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 18:45:46 by vmartins          #+#    #+#             */
/*   Updated: 2018/01/22 18:50:17 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"

static	inline	t_hist		*init_history(void)
{
	t_hist					*h;

	h = NULL;
	if ((h = (t_hist *)malloc(sizeof(t_hist))) == NULL)
	{
		ft_putendl_fd("Error malloc", 2);
		return (NULL);
	}
	h->begin = NULL;
	h->end = NULL;
	h->current = NULL;
	h->ecrase_hist = 0;
	return (h);
}

static	inline	t_keyflag	*init_keyflag(void)
{
	t_keyflag				*new;

	if ((new = (t_keyflag *)malloc(sizeof(*new))) == NULL)
	{
		ft_putendl_fd("Error malloc", 2);
		return (NULL);
	}
	new->underline = 0;
	new->cl = 0;
	return (new);
}

static	inline	t_auto		*init_autocompletion(void)
{
	t_auto					*autoc;

	autoc = NULL;
	if ((autoc = (t_auto *)malloc(sizeof(t_auto))) == NULL)
		return (NULL);
	autoc->str = NULL;
	autoc->end = NULL;
	autoc->current = NULL;
	autoc->begin = NULL;
	autoc->finish = 0;
	autoc->jump = 0;
	autoc->max_len = 0;
	autoc->row = 0;
	autoc->col = 0;
	autoc->pages = 0;
	autoc->more_pages = 0;
	autoc->nbr_word = 0;
	autoc->updaterow = 0;
	autoc->arrow = 0;
	autoc->clr_yes = 0;
	autoc->can_print = 0;
	autoc->possiblitie = 0;
	return (autoc);
}

static	inline	t_dlst		*init_lineterm(void)
{
	t_dlst					*line;

	line = NULL;
	if ((line = (t_dlst *)malloc(sizeof(t_dlst))) == NULL)
	{
		ft_putendl_fd("Error malloc", 2);
		return (NULL);
	}
	line->lnk_before = 0;
	line->last = 0;
	line->begin = NULL;
	line->end = NULL;
	return (line);
}

void						ft_init_termc2(t_termc **tsh)
{
	if (((*tsh)->line = init_lineterm()) == NULL)
		ft_putendl_fd("Error init_lineterm", 2);
	if (((*tsh)->line_dup = init_lineterm()) == NULL)
		ft_putendl_fd("Error init_lineterm", 2);
	if (((*tsh)->histmp = init_history()) == NULL)
		ft_putendl_fd("Error init_history", 2);
	if (((*tsh)->histlist = init_history()) == NULL)
		ft_putendl_fd("Error init_history", 2);
	if (((*tsh)->console = init_console()) == NULL)
		ft_putendl_fd("Error init_console", 2);
	if (((*tsh)->autoc = init_autocompletion()) == NULL)
		ft_putendl_fd("Error init_autocompletion", 2);
	if (((*tsh)->keyflag = init_keyflag()) == NULL)
		ft_putendl_fd("Error init_keyflag", 2);
}
