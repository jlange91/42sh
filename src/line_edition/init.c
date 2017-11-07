/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 19:23:20 by stvalett          #+#    #+#             */
/*   Updated: 2017/10/10 15:26:51 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/line_edition.h"
#include "../../inc/env_term.h"
#include "../../inc/autocompletion.h"

static	inline	t_console	*init_console(void)
{
	t_console	*console;

	console = NULL;
	if ((console = (t_console *)malloc(sizeof(t_console))) == NULL)
	{
		return (NULL);
	}
	console->total_line = 0;
	console->line_pos = 1;
	console->char_pos = 0;
	return (console);
}

static	inline	t_term		*init_term(t_env *env)
{
	t_term	*term;
    char    *str;

	term = NULL;
    str = NULL;
	if ((term = (t_term *)malloc(sizeof(t_term))) == NULL)
		return (NULL);
	ft_memset(term->bp, '\0', 2048);
	ft_memset(term->area, '\0', 2048);
    str = ft_getenv("TERM", env);
	if (tgetent(term->bp, str) < 0)
    {
		ft_putendl_fd("Error , tgetent ", 2);
		return (NULL);
    }
    free(str);
	term->lestr = tgetstr("le", (char **)term->area);
	term->dcstr = tgetstr("dc", (char **)term->area);
	term->ndstr = tgetstr("nd", (char **)term->area);
	term->cbstr = tgetstr("cb", (char **)term->area);
	term->dlstr = tgetstr("dl", (char **)term->area);
	term->dostr = tgetstr("do", (char **)term->area);
	term->upstr = tgetstr("up", (char **)term->area);
	term->cdstr = tgetstr("cd", (char **)term->area);
	term->cestr = tgetstr("ce", (char **)term->area);
	term->clrstr = tgetstr("cl", (char **)term->area);
	term->vistr = tgetstr("vi", (char **)term->area);
	term->vestr = tgetstr("ve", (char **)term->area);
	term->usstr = tgetstr("us", (char **)term->area);
	term->uestr = tgetstr("ue", (char **)term->area);
	return (term);
}

static	inline	hlist		*init_history(void)
{
	hlist	*h;

	h = NULL;
	if ((h = (hlist *)malloc(sizeof(hlist))) == NULL)
	{
		ft_putendl_fd("Error malloc", 2);
		return (NULL);
	}
	h->begin = NULL;
	h->end = NULL;
	h->current = NULL;
	h->active = 0;
    h->ecrase_hist = 0;
    h->down = 0;
    h->up = 0;
    h->line_history = 0;
	return (h);
}

static  inline  t_keyflag   *init_keyflag(void)
{
    t_keyflag   *new;

    if ((new = (t_keyflag *)malloc(sizeof(*new))) == NULL)
    {
        ft_putendl_fd("Error malloc", 2);
        return (NULL);
    }
    new->backspace = 0;
    new->mleft = 0;
    new->mright = 0;
    new->underline = 0;
    new->cl = 0;
    return (new);
}

static	inline	t_auto		*init_autocompletion(void)
{
    t_auto   *autocomp;

	autocomp = NULL;
	if ((autocomp = (t_auto *)malloc(sizeof(t_auto))) == NULL)
	{
		ft_putendl_fd("Error malloc", 2);
		return (NULL);
	}
    autocomp->str = NULL;
	autocomp->end = NULL;
    autocomp->current = NULL;
	autocomp->begin = NULL;
    autocomp->finish = 0;
    autocomp->jump = 0;
    autocomp->max_len = 0;
    autocomp->row = 0;
    autocomp->col = 0;
    autocomp->pages = 0;
    autocomp->more_pages = 0;
    autocomp->nbr_word = 0;
    autocomp->updaterow = 0;
    autocomp->arrow = 0;
    autocomp->clr_yes = 0;
	autocomp->can_print = 0;
	autocomp->possiblitie = 0;
	return (autocomp);
}

static	inline	dlist		*init_lineterm(void)
{
	dlist	*line;

	line = NULL;
	if ((line = (dlist *)malloc(sizeof(dlist))) == NULL)
	{
		ft_putendl_fd("Error malloc", 2);
		return (NULL);
	}
	line->lenght = 0;
	line->lnk_before = 0;
	line->last = 0;
	line->begin = NULL;
	line->end = NULL;
	return (line);
}

t_shell						*init_shell(t_env *env)
{
	t_shell	*shell;

	shell = NULL;
	if ((shell = (t_shell *)malloc(sizeof(t_shell))) == NULL)
	{
		ft_putendl_fd("Error malloc", 2);
		return (NULL);
	}
    if ((shell->term = init_term(env)) == NULL)
		ft_putendl_fd("Error init_term", 2);
	if ((shell->line = init_lineterm()) == NULL)
		ft_putendl_fd("Error init_lineterm", 2);
	if ((shell->line_dup = init_lineterm()) == NULL)
		ft_putendl_fd("Error init_lineterm", 2);
	if ((shell->history = init_history()) == NULL)
		ft_putendl_fd("Error init_history", 2);
	if ((shell->from_hist = init_history()) == NULL)
		ft_putendl_fd("Error init_history", 2);
	if ((shell->console = init_console()) == NULL)
		ft_putendl_fd("Error init_console", 2);
    if ((shell->autocompl = init_autocompletion()) == NULL)
        ft_putendl_fd("Error init_autocompletion", 2);
    if ((shell->autocompl_binary = init_autocompletion()) == NULL)
        ft_putendl_fd("Error init_autocompletion_binary", 2);
	if ((shell->keyflag = init_keyflag()) == NULL)
		ft_putendl_fd("Error init_keyflag", 2);
    ft_init_fill_history(shell->from_hist);
    ft_init_autocompl_binary(shell, env);
    shell->nbr_hist = 0;
    shell->ret_signal = 0;
    shell->move_cursor = 0;
    shell->auto_active = 0;
    shell->multiauto_active = 0;
    shell->count_tab = 0;
    shell->len_prompt = 0;
	shell->quotes = 0;
	return (shell);
}
