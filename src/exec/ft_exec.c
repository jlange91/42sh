/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 18:39:25 by jlange            #+#    #+#             */
/*   Updated: 2017/11/03 18:41:16 by jlange           ###   ########.fr       */
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
	path = fill_path(env);
	ret = 2;
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

void					ft_exec(char **av, char **env)
{
	int		status;
	pid_t	father;
	int		ret;

	father = fork();
	if (father > 0)
	{
		signal(SIGINT, SIG_IGN);
		wait(&status);
		ft_singleton(status, 1);
		signal(SIGINT, ft_handle_signal);
	}
	if (father == 0)
	{
		ret = (av[0][0] == '/' || (av[0][0] == '.' && (av[0][1] == '.' ||
		av[0][1] == '/'))) ? exec_av(av, env) : exec_path(av, env);
		if (ret != 0)
		{
			ft_putstr_fd("42sh: command not found: ", 2);
			ft_putendl_fd(av[0], 2);
			exit(1);
		}
	}
}
