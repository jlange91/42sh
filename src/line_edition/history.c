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

char	*ft_lnk_to_str(t_lineterm *begin, t_termc *tsh) // TOOLS PR TOUT
{
	char		*str;
	t_lineterm	*tmp;
	int			i;

	str = NULL;
	tmp = begin;
	if (tmp)
	{
		if ((str = (char *)malloc(sizeof(char) *
						ft_count_dlnk(tsh, 0) + 1)) == NULL)
			return (NULL);
		if (tmp->next)
            tmp = ft_dontGetPrompt2(tmp);
		i = 0;
		while (tmp)
		{
			str[i++] = tmp->c;
			tmp = tmp->next;
		}
		str[i] = '\0';
	}
	return (str);
}

int 	ft_useless(char *line)
{
	int i;

	i = 0;
	while (line[i] && ft_isdigit(line[i]))
		i++;
	if (line[i] == ' ')
		return (i + 1);
	return (0);
}

int		ft_find_history(t_termc *tsh)
{
    t_history   *hist;
    char        *str;

    hist = NULL;
    str = NULL;
    hist = tsh->histlist->begin;
    if (!hist || !tsh->histlist)
        return (0);
    else
    {
	    ft_free_history(tsh->histmp);
        if ((str = ft_lnk_to_str(tsh->line->begin, tsh)) != NULL)
        {
            while (hist)
		    {
			    if (!ft_strncmp(str, &hist->data[ft_useless(hist->data)],\
					ft_strlen(str)))
				    push_backhist(tsh->histmp,\
					&hist->data[ft_useless(hist->data)], hist->index, hist->new);
                hist = hist->next;
		    }
			push_backhist(tsh->histmp, "", -1, 0);
			tsh->histmp->current = tsh->histmp->end;
		    free(str);
	    }
    }
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
				push_backhist(tsh->histmp, &hist->data[ft_useless(hist->data)],\
				hist->index, hist->new);
			hist = hist->next;
		}
		push_backhist(tsh->histmp, "", -1, 0);
		tsh->histmp->current = tsh->histmp->end;
    }
	return (1);
}

int    ft_init_fill_history(hlist *histlist)
{
    char    *line;
    int     fd;
    int     i;
    int     ret;

    i = 0;
	fd = open(&NAME_HIST[1], O_RDONLY);
	if (fd < 0)
		return (0);
	line = NULL;
    while ((ret = get_next_line(fd, &line)) > 0)
	{
		push_backhist(histlist, &line[ft_useless(line)], ++i, 0);
		free(line);
	}
    close(fd);
    return (1);
}
