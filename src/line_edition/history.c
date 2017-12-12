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
						ft_count_dlnk(tsh) + 1)) == NULL)
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

int     ft_count_history(char *path)
{
    int     fd;
    int     count;
    int     ret;
    char    *line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	line = NULL;
    count = 0;
    while ((ret = get_next_line(fd, &line)) > 0)
	{
        count++;
		free(line);
	}
    close(fd);
    return (count);
}

int		ft_find_history(t_termc *tsh)
{
    t_history   *begin;
    char        *str;

    begin = NULL;
    str = NULL;
    begin = tsh->from_hist->begin;
    if (!begin || !tsh->from_hist)
        return (0);
    else
    {
	    ft_free_history(tsh->history);
        if ((str = ft_lnk_to_str(tsh->line->begin, tsh)) != NULL)
        {
            while (begin)
		    {
			    if (ft_strncmp(str, begin->data, ft_strlen(str)) == 0)
				    ft_fill_back_hlst(tsh->history, begin->data);
                begin = begin->next;
		    }
			ft_fill_back_hlst(tsh->history, "");
		    free(str);
		    tsh->history->current = tsh->history->end;
	    }
    }
	return (1);
}

int		ft_fill_history(t_termc *tsh)
{
    t_history   *begin;
	static int 	count;

    begin = NULL;
	if (count++ < 1)
		tsh->from_hist->pwd = ft_strjoin(tsh->pwd, "/.21sh_history");
    begin = tsh->from_hist->begin;
    if (!begin || !tsh->from_hist)
        return (0);
    else
    {
        ft_free_history(tsh->history);
        while (begin)
        {
            ft_fill_back_hlst(tsh->history, begin->data);
            begin = begin->next;
        }
	    ft_fill_back_hlst(tsh->history, "");
	    tsh->history->current = tsh->history->end;
    }
	return (1);
}

int    ft_init_fill_history(hlist *from_hist)
{
    char    *line;
    int     fd;
    int     i;
    int     ret;
    int     res;

    i = 0;
	fd = open(".21sh_history", O_RDONLY);
	if (fd < 0)
		return (0);
	line = NULL;
    res = ft_count_history(".21sh_history");
    while ((ret = get_next_line(fd, &line)) > 0)
	{
        if (i++ >= res - 500)
		    ft_fill_back_hlst(from_hist, line);
		free(line);
	}
    close(fd);
    return (1);
}
