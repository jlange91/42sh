/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdpath.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 16:21:11 by vmartins          #+#    #+#             */
/*   Updated: 2018/01/22 16:22:33 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"
#include "../../inc/built_in.h"

static	inline	char	**fill_path_tab(char **env)
{
	char				**path;
	int					i;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (!ft_strncmp("CDPATH=", env[i], ft_strlen("CDPATH=")))
		{
			path = ft_strsplit(&env[i][7], ':');
			return (path);
		}
		i++;
	}
	return (NULL);
}

int						try_path(char *path, int opt)
{
	if (opt == 0)
		return (ft_cd_l(path, 0));
	else
		return (ft_cd_p(path, 0));
}

static	inline	void	fill_collins(char *str1, char *str2, int *j)
{
	int					i;

	i = 0;
	if (str1)
	{
		while (str1[i])
		{
			str2[*j] = str1[i];
			i++;
			*j += 1;
		}
		i = 0;
	}
}

static	inline	char	*fill_path(char *str1, char *str2)
{
	char				*line;
	int					len;
	int					j;

	j = 0;
	len = (str1) ? ft_strlen(str1) : 0;
	len += (str1[len - 1] == '/') ? 0 : 1;
	len += (str2) ? ft_strlen(str2) : 0;
	line = (char*)malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	fill_collins(str1, line, &j);
	if (str1[ft_strlen(str1) - 1] != '/')
		fill_collins("/", line, &j);
	fill_collins(str2, line, &j);
	line[j] = 0;
	return (line);
}

int						ft_try_cdpath(char *word, char **env, int opt)
{
	char				**path;
	char				*l_path;
	int					i;

	if (word[0] == '/' || word[0] == '.')
		return (0);
	i = 0;
	path = fill_path_tab(env);
	while (path && path[i])
	{
		l_path = fill_path(path[i], word);
		if (try_path(l_path, opt) == 0)
		{
			free(l_path);
			free_tab_2d(path);
			return (1);
		}
		free(l_path);
		i++;
	}
	free_tab_2d(path);
	return (0);
}
