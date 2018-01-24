/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_autocompletion2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 17:53:00 by stvalett          #+#    #+#             */
/*   Updated: 2018/01/22 14:25:20 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/autocompletion.h"

/*
**@function
**@param
**@return
*/

int					ft_check_open(char *line)
{
	int				i;
	int				k;
	char			*res;
	char			**ttab;
	struct stat		info;

	ft_memset(&info, 0, sizeof(info));
	ttab = ft_strsplit2(line);
	i = ft_count_dtab(ttab) - 1;
	if ((res = (char *)malloc(sizeof(char) * (ft_strlen(ttab[i]) + 1))) == NULL)
		exit(1);
	k = -1;
	while (ttab[i][++k] && ttab[i][k] != '/')
		res[k] = ttab[i][k];
	res[k] = '\0';
	stat(res, &info);
	if (S_ISDIR(info.st_mode))
	{
		ft_free_tab(ttab);
		free(res);
		return (1);
	}
	ft_free_tab(ttab);
	free(res);
	return (0);
}

/*
**@function
**@param
**@return
*/

static	int			ft_count_basic(t_lineterm *end)
{
	int				i;

	if (!end)
		return (-1);
	i = 0;
	while (end && end->c != ' ' && end->index != 0)
	{
		i++;
		end = end->prev;
	}
	return (i);
}

/*
**@function
**@param
**@return
*/

static	char		*ft_get_word(t_termc *tsh, int i)
{
	char			*word;
	t_lineterm		*end;

	word = NULL;
	if (!tsh->line)
		return (word);
	if ((i = ft_count_basic(tsh->line->end)) == -1)
		return (word);
	if ((word = (char *)malloc(sizeof(char) * (i + 1))) == NULL)
		return (NULL);
	end = find_cursor(tsh->line->end, 0);
	i = 0;
	while (end && end->c != ' ' && end->index != 0)
	{
		word[i] = end->c;
		i++;
		end = end->prev;
	}
	word[i] = '\0';
	ft_reverse(word);
	return (word);
}

/*
**@function
**@param
**@return
*/

static int			ft_split_simple(int dot, char *file, char *tmp)
{
	struct stat		info;

	ft_memset(&info, 0, sizeof(struct stat));
	stat(file, &info);
	if (file[0] != '.')
		return (1);
	if (file[0] == '.' && file[1] != '.'
			&& dot == 1 && S_ISDIR(info.st_mode))
	{
		if (tmp && !ft_strncmp(file, tmp, ft_strlen(tmp)))
			return (1);
	}
	if (file[0] == '.' && file[1] != '.'
			&& dot == 2 && S_ISREG(info.st_mode))
	{
		if (tmp && !ft_strncmp(file, tmp, ft_strlen(tmp)))
			return (1);
	}
	return (0);
}

/*
**@function	For start or if line == SPACE, Opencurrent dir
**			and fill struct autoc
**@param	1 = struct t_termc *tsh
**@return
*/

void				ft_init_simple_autocompl(t_termc *tsh, int dot, char *line)
{
	int				i;
	char			*tmp;
	DIR				*path;
	struct dirent	*file;

	i = 1;
	if (dot && line)
		tmp = ft_get_word(tsh, i);
	if ((path = opendir(".")) != NULL)
	{
		ft_free_autocompletion(&tsh->autoc);
		while ((file = readdir(path)) != NULL)
		{
			if (ft_split_simple(dot, file->d_name, tmp))
				ft_fill_back_autocompl(tsh->autoc, file->d_name, i++);
		}
		tsh->autoc->current = tsh->autoc->begin;
		closedir(path);
	}
	if (dot && line != NULL && tmp != NULL)
		free(tmp);
}
