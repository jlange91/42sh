/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_autocompletion2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 17:53:00 by vmartins          #+#    #+#             */
/*   Updated: 2018/03/06 16:21:22 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/autocompletion.h"

/*
**@function
**@param
**@return
*/

int					ft_check_open2(char *tmp, char **ttab, char *res)
{
	struct stat		info;

	ft_memset(&info, 0, sizeof(info));
	stat(tmp, &info);
	free(tmp);
	ft_free_tab(ttab);
	if (S_ISDIR(info.st_mode) || res[0] == '/')
	{
		free(res);
		return (1);
	}
	free(res);
	return (0);
}

int					ft_check_open(char *line)
{
	int				i;
	int				k;
	char			*res;
	char			*tmp;
	char			**ttab;

	ttab = ft_strsplit2(line);
	i = ft_count_dtab(ttab) - 1;
	if ((res = (char *)malloc(sizeof(char) * (ft_strlen(ttab[i]) + 1))) == NULL)
		exit(1);
	k = -1;
	while (ttab[i][++k] && ttab[i][k] != ' ')
		res[k] = ttab[i][k];
	res[k] = '\0';
	tmp = ft_remove_useless_path(res);
	return (ft_check_open2(tmp, ttab, res));
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
	DIR				*path;
	struct dirent	*file;

	(void)line;
	i = 1;
	if ((path = opendir(".")) != NULL)
	{
		ft_free_autocompletion(&tsh->autoc);
		while ((file = readdir(path)) != NULL)
		{
			if (dot && file->d_name[1] != '.')
				ft_fill_back_autocompl(tsh->autoc, file->d_name, i++);
			else if (!dot && file->d_name[0] != '.')
				ft_fill_back_autocompl(tsh->autoc, file->d_name, i++);
		}
		tsh->autoc->current = tsh->autoc->begin;
		closedir(path);
	}
}
