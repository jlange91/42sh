/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 16:22:25 by vmartins          #+#    #+#             */
/*   Updated: 2018/01/30 16:22:26 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"
#include "../../inc/line_edition.h"

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

static inline int		exec_path(char **av, char **env)
{
	char	**path;
	char	*l_path;
	int		i;
	int		ret;

	i = 0;
	ret = 2;
	execve(ft_return_hash(av[0]), av, env);
	path = fill_path(env);
	while (path && path[i])
	{
		l_path = ft_replace_line(path[i], "/", av[0]);
		if (execve(l_path, av, env) != -1)
		{
			ret = 0;
			break ;
		}
		ret = errno;
		free(l_path);
		i++;
	}
	free_tab_2d(path);
	return (ret);
}

static inline int		exec_av(char **av, char **env)
{
	int ret;

	ret = execve(av[0], av, env);
	ret = (ret == -1) ? errno : 0;
	return (ret);
}

void					ft_exec_pipe(char **av, char **env)
{
	int		ret;

	ft_fill_hash(av, env);
	ret = (av[0][0] == '/' || (av[0][0] == '.' && (av[0][1] == '.' ||
					av[0][1] == '/'))) ? exec_av(av, env) : exec_path(av, env);
	if (ret != 0)
	{
		if (ret == 2)
		{
			ft_putstr_fd("shell: command not found: ", 2);
			ft_putendl_fd(av[0], 2);
		}
		else
			ft_perror("shell", ret, av[0]);
		exit(1);
	}
}
