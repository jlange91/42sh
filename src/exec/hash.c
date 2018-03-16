/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 14:30:48 by jlange            #+#    #+#             */
/*   Updated: 2018/01/23 15:27:05 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"

int						check_access(char *name, char *path)
{
	t_shell	*sh;
	DIR		*dir;

	dir = NULL;
	if (access(path, F_OK | X_OK) == 0 && !(dir = opendir(path)))
	{
		sh = ft_ret_sh(NULL);
		ft_add_hash(name, path);
		return (1);
	}
	else
	{
		if (dir)
			closedir(dir);
		return (0);
	}
}

static inline char		**fill_path(char **env)
{
	char	**path;
	int		i;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (!ft_strncmp("PATH=", env[i], ft_strlen("PATH=")))
		{
			path = ft_strsplit(&env[i][5], ':');
			return (path);
		}
		i++;
	}
	return (NULL);
}

int						ft_fill_hash(char **av, char **env)
{
	t_shell	*sh;
	char	**path;
	char	*l_path;
	int		i;

	i = 0;
	if (access(ft_return_hash(av[0]), F_OK | X_OK) == 0)
		return (1);
	sh = ft_ret_sh(NULL);
	path = fill_path(env);
	while (path && path[i])
	{
		l_path = ft_replace_line(path[i], "/", av[0]);
		if (check_access(av[0], l_path) == 1)
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
