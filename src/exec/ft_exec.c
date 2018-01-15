/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 18:39:25 by jlange            #+#    #+#             */
/*   Updated: 2018/01/15 18:53:12 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"
#include "../../inc/line_edition.h"
#include "../../inc/built_in.h"

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

int		cd_or_error(t_cmd *cmd, int status)
{

	if (status == 0)
		return (0);
	else if (status != 10752)
		return (1);		
	ft_cd(cmd, 1);
	return (0);
}

void					ft_exec(t_cmd *cmd, char **av, char **env)
{
	int		status;
	pid_t	father;
	int		ret;

	search_hash(av, env);
	father = fork();
	if (father > 0)
	{
		signal(SIGINT, SIG_IGN);
		wait(&status);
		if (cd_or_error(cmd, status) == 1)
			ft_singleton(status, 1);
		signal(SIGINT, ft_handle_signal);
	}
	else if (father == 0)
	{
		ret = (av[0][0] == '/' || (av[0][0] == '.' && (av[0][1] == '.' ||
		av[0][1] == '/'))) ? exec_av(av, env) : exec_path(av, env);
		if (ret != 0)
		{
			DIR		*dir;
			if ((dir = opendir(cmd->av[0])))
				exit(42);
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
	else
		ft_perror("fork", errno, NULL);
}
