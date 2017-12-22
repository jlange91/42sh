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
	if (str == NULL || !str[5] || !ft_strcmp(&str[5], "xterm-256color"))
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
	if (ret)
		free(str);
	return (term);
}

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
    ft_init_fill_history(tsh->histfile);
	tsh->pwd = NULL;
    tsh->ret_signal = 0;
    tsh->auto_active = 0;
    tsh->multiauto_active = 0;
    tsh->key_tab = 0;
    tsh->len_prompt = 0;
	tsh->quotes = 0;
	tsh->repl = 0;
	tsh->sigint = 0;
	return (tsh);
}
