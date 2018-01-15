/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <stvalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 19:23:12 by stvalett          #+#    #+#             */
/*   Updated: 2017/11/17 10:01:34 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/line_edition.h"
#include "../../inc/sh21.h"
#include "../../inc/quote.h"

int		ft_find_history(t_termc *tsh)
{
    t_history   *hist;
    char        *str;

    hist = NULL;
    str = NULL;
    hist = tsh->histlist->begin;
    if (!hist || !tsh->histlist)
        return (0);
	ft_free_history(tsh->histmp);
	str = (tsh->quotes) ? ft_to_str(tsh, 1) : ft_to_str(tsh, 0);
    while (hist)
	{
		if (!ft_strncmp(str, hist->data, ft_strlen(str)))
			push_backhist(tsh->histmp, hist->data, hist->index, hist->new);
        hist = hist->next;
	}
	push_backhist(tsh->histmp, "", -1, 0);
	tsh->histmp->current = tsh->histmp->end;
	free(str);
	return (1);
}

int		ft_fill_history(t_termc *tsh)
{
    t_history   *hist;
	static int 	count;

    hist = NULL;
	if (count++ < 1)
		tsh->histlist->pwd = ft_strjoin(ft_var_pwd(NULL), NAME_HIST);
    hist = tsh->histlist->begin;
    if (!hist || !tsh->histlist)
        return (0);
    else
    {
		ft_free_history(tsh->histmp);
		while (hist)
		{
			if (hist->print)
				push_backhist(tsh->histmp, hist->data, hist->index, hist->new);
			hist = hist->next;
		}
		push_backhist(tsh->histmp, "", -1, 0);
		tsh->histmp->current = tsh->histmp->end;
    }
	return (1);
}

t_history *ft_concat_string(t_history *begin, hlist *histlist, int i)
{
	char *tmp;

	tmp = NULL;
	ft_join_all(begin->data, &tmp, 0);
	tmp = ft_free_join(tmp, "\n", 'L');
	begin = begin->next;
	while (begin)
	{
		if (ft_check_quote(begin->data) != 0)
		{
			ft_join_all(begin->data, &tmp, 0);
			push_backhist(histlist, tmp, ++i, 0);
			begin = begin->next;
			break;
		}
		else
		{
			ft_join_all(begin->data, &tmp, 0);
			tmp = ft_free_join(tmp, "\n", 'L');
		}
		begin = begin->next;
	}
	free(tmp);
	return (begin);
}

void 	ft_format_string(hlist *tmp, hlist *histlist)
{
	int 	i;

	i = 0;
	while (tmp->begin)
	{
		if (ft_check_quote(tmp->begin->data) != 0)
			tmp->begin = ft_concat_string(tmp->begin, histlist, i);
		else
		{
			push_backhist(histlist, tmp->begin->data, ++i, 0);
			tmp->begin = tmp->begin->next;
		}
	}
}

int    	ft_init_fill_history(hlist *histlist)
{
    int     fd;
    int     i;
    int     ret;
	char    *line;
	hlist 	*tmp;

	tmp = NULL;
	if ((tmp = (hlist *)malloc(sizeof(hlist))) == NULL)
		exit (1);
	tmp->begin = NULL;
	tmp->current = NULL;
	tmp->end = NULL;
	i = 0;
	fd = open(&NAME_HIST[1], O_RDONLY);
	if (fd < 0)
		return (0);
	line = NULL;
    while ((ret = get_next_line(fd, &line)) > 0)
	{
		push_backhist(tmp, line, ++i, 0);
		free(line);
	}
	ft_format_string(tmp, histlist);
	ft_free_history(tmp);
	free(tmp);
    close(fd);
    return (1);
}
