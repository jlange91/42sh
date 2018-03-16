/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_autocompletion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 17:27:25 by vmartins          #+#    #+#             */
/*   Updated: 2018/03/06 16:17:22 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/autocompletion.h"

/*
**@function	Split from function ft_slash_here
**@param	1 = limit is limit index we can copy
**			2 = len for malloc good size
**			3 = word who must be parse
**@return	New world before "/"
*/

static	char		*ft_slash_here_bis(int limit, int len, char *str)
{
	char			*new;
	int				j;

	if ((new = (char *)malloc(sizeof(char) *
					((ft_strlen(str) - len) + 1))) == NULL)
		return (NULL);
	j = -1;
	while (str[++j])
	{
		if (j == limit)
		{
			if (j == 0)
			{
				new[j] = str[j];
				j++;
			}
			break ;
		}
		new[j] = str[j];
	}
	new[j] = '\0';
	return (new);
}

/*
**@function	Find_slash if here
**@param	1 = word who must be parse
**@return	The new word before "/"
**			else NULL
*/

static	char		*ft_slash_here(char *str)
{
	char			*new;
	int				i;
	int				count;

	new = NULL;
	count = 0;
	i = ft_strlen(str) - 1;
	if (str[i] != '/')
	{
		while (str[i] && str[i] != '/')
		{
			if (i == 0)
				return (new);
			count++;
			i--;
		}
		new = ft_slash_here_bis(i, count, str);
	}
	return (new);
}

/*
**@function	Open and fill with good path
**@param	1 = struct t_termc *tsh
**			2 = PATH
**			3 = flag for no print if is 1
**@return	always TRUE
*/

static	int			ft_open_and_fill(t_termc *tsh, DIR *path, int nbr)
{
	int				i;
	struct dirent	*file;

	i = 1;
	ft_free_autocompletion(&tsh->autoc);
	while ((file = readdir(path)) != NULL)
		if (file->d_name[0] != '.' && file->d_name[1] != '.')
			ft_fill_back_autocompl(tsh->autoc, file->d_name, i++);
	if (!tsh->autoc->begin && nbr == 1)
		tsh->auto_active = 0;
	tsh->autoc->current = tsh->autoc->begin;
	closedir(path);
	return (1);
}

/*
**@function 3 methode for open, word complete, last word in tab or
**			word before "/"
**@param	1 = struct t_termc *tsh
**			2 = word to find
**			3 = flag for return
**@return	return flag
*/

static	void		ft_try_open(t_termc *tsh, char *line, int *flag)
{
	int				i;
	char			*tmp;
	char			**tab_word;
	DIR				*path;

	if ((path = opendir(line)) != NULL)
		*flag = ft_open_and_fill(tsh, path, 1);
	else if ((tab_word = ft_strsplit2(line)) != NULL)
	{
		i = ft_count_dtab(tab_word) - 1;
		if ((path = opendir(tab_word[i])) != NULL)
			*flag = ft_open_and_fill(tsh, path, 2);
		else if ((tmp = ft_slash_here(tab_word[i])) != NULL)
		{
			if ((path = opendir(tmp)) != NULL)
			{
				ft_open_and_fill(tsh, path, 2);
				*flag = 0;
			}
			free(tmp);
		}
		ft_free_tab(tab_word);
	}
	else
		ft_init_simple_autocompl(tsh, 0, line);
}

/*
**@function	Reset autocomp if line == SPACE
**			else try open and find word
**@param	1 = struct t_termc *tsh
**			2 = the word we must find
**@return	1 is TRUE , 0 is FALSE
*/

int					ft_init_autocompl(t_termc *tsh, char *line)
{
	int				flag;

	flag = 0;
	if (line && line[ft_strlen(line) - 1] == ' ')
	{
		ft_init_simple_autocompl(tsh, 0, NULL);
		return (1);
	}
	else if (line != NULL && line[ft_strlen(line) - 1] != '/'
			&& ((line[0] == '.' || line[ft_strlen(line) - 1] == '.')))
		ft_init_simple_autocompl(tsh, 1, line);
	else if (line != NULL && ft_strchr(line, '.') != NULL
			&& !ft_check_open(line) && line[0] != '.' &&
			line[ft_strlen(line) - 1] != '/')
	{
		ft_init_simple_autocompl(tsh, 2, line);
		if (tsh->autoc)
			return (1);
	}
	else
		ft_try_open(tsh, line, &flag);
	return (flag);
}
