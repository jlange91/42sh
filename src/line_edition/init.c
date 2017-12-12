/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 19:23:20 by stvalett          #+#    #+#             */
/*   Updated: 2017/11/16 19:33:43 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"

// static	inline	t_console	*init_console(void)
// {
// 	t_console	*console;
//
// 	console = NULL;
// 	if ((console = (t_console *)malloc(sizeof(t_console))) == NULL)
// 	{
// 		return (NULL);
// 	}
// 	console->total_line = 0;
// 	console->line_pos = 1;
// 	console->char_pos = 0;
// 	return (console);
// }

static	inline	t_term		*init_term(char **env)
{
	t_term	*term;
    char    *str;
	int		ret;

	term = NULL;
    str = NULL;
	ret = 0;
	if ((term = (t_term *)malloc(sizeof(t_term))) == NULL)
		return (NULL);
	ft_memset(term->bp, '\0', 2048);
	ft_memset(term->area, '\0', 2048);
    str = ft_getenv("TERM", env);
	if (ft_strcmp(&str[5], "xterm-256color") != 0)
	{
		str = ft_strdup("TERM=xterm-256color");
		ret = 1;
	}
	if (tgetent(term->bp, &str[5]) < 0)
		ft_putendl_fd("Error Tgetent", 2);
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
	if (ret)
		free(str);
	return (term);
}

// static	inline	hlist		*init_history(void)
// {
// 	hlist	*h;
//
// 	h = NULL;
// 	if ((h = (hlist *)malloc(sizeof(hlist))) == NULL)
// 	{
// 		ft_putendl_fd("Error malloc", 2);
// 		return (NULL);
// 	}
// 	h->begin = NULL;
// 	h->end = NULL;
// 	h->current = NULL;
// 	h->active = 0;
//     h->ecrase_hist = 0;
//     h->down = 0;
//     h->up = 0;
//     h->line_history = 0;
// 	return (h);
// }
//
// static  inline  t_keyflag   *init_keyflag(void)
// {
//     t_keyflag   *new;
//
//     if ((new = (t_keyflag *)malloc(sizeof(*new))) == NULL)
//     {
//         ft_putendl_fd("Error malloc", 2);
//         return (NULL);
//     }
//     new->backspace = 0;
//     new->mleft = 0;
//     new->mright = 0;
//     new->underline = 0;
//     new->cl = 0;
//     return (new);
// }
//
// static	inline	t_auto		*init_autocompletion(void)
// {
//     t_auto   *autoc;
//
// 	autoc = NULL;
// 	if ((autoc = (t_auto *)malloc(sizeof(t_auto))) == NULL)
// 	{
// 		ft_putendl_fd("Error malloc", 2);
// 		return (NULL);
// 	}
//     autoc->str = NULL;
// 	autoc->end = NULL;
//     autoc->current = NULL;
// 	autoc->begin = NULL;
//     autoc->finish = 0;
//     autoc->jump = 0;
//     autoc->max_len = 0;
//     autoc->row = 0;
//     autoc->col = 0;
//     autoc->pages = 0;
//     autoc->more_pages = 0;
//     autoc->nbr_word = 0;
//     autoc->updaterow = 0;
//     autoc->arrow = 0;
//     autoc->clr_yes = 0;
// 	autoc->can_print = 0;
// 	autoc->possiblitie = 0;
// 	return (autoc);
// }

// static	inline	dlist		*init_lineterm(void)
// {
// 	dlist	*line;
//
// 	line = NULL;
// 	if ((line = (dlist *)malloc(sizeof(dlist))) == NULL)
// 	{
// 		ft_putendl_fd("Error malloc", 2);
// 		return (NULL);
// 	}
// 	line->lenght = 0;
// 	line->lnk_before = 0;
// 	line->last = 0;
// 	line->begin = NULL;
// 	line->end = NULL;
// 	return (line);
// }

t_termc						*init_termc(char **env)
{
	t_termc	*tsh;

	tsh = NULL;
	if ((tsh = (t_termc *)malloc(sizeof(t_termc))) == NULL)
	{
		ft_putendl_fd("Error malloc", 2);
		return (NULL);
	}
    if ((tsh->term = init_term(env)) == NULL)
		ft_putendl_fd("Error init_term", 2);
	ft_init_termc2(&tsh);
    ft_init_fill_history(tsh->from_hist);
    ft_init_autocompl_binary(tsh, env);
	tsh->pwd = NULL;
    tsh->nbr_hist = 0;
    tsh->ret_signal = 0;
    tsh->move_cursor = 0;
    tsh->auto_active = 0;
    tsh->multiauto_active = 0;
    tsh->count_tab = 0;
    tsh->len_prompt = 0;
	tsh->quotes = 0;
	return (tsh);
}
