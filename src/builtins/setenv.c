/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 18:26:30 by jlange            #+#    #+#             */
/*   Updated: 2018/01/23 14:44:02 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"

static inline int		ft_ret(t_cmd *cmd)
{
	int i;

	i = -1;
	if (cmd->ac < 2)
	{
		ft_display_env(ft_var_env(NULL));
		return (1);
	}
	else if (cmd->ac > 3)
	{
		ft_putstr_fd("setenv: Too many arguments.\n", 2);
		ft_singleton(1, 1);
		return (1);
	}
	while (cmd->av[1][++i])
	{
		if (!ft_isalnum(cmd->av[1][i]))
		{
			ft_putstr_fd("setenv: Variable name must contain alphanumeric \
characters.\n", 2);
			ft_singleton(1, 1);
			return (1);
		}
	}
	return (0);
}

static inline char		*create_line(char *name, char *value)
{
	char	*line;
	char	*tmp;

	line = ft_strjoin(name, "=");
	tmp = line;
	line = (value) ? ft_strjoin(tmp, value) : ft_strdup(line);
	free(tmp);
	return (line);
}

static inline char		**change_line(char *name, char *value, char **env)
{
	int		i;
	char	**new_env;
	char	*name2;

	i = 0;
	name2 = ft_strjoin(name, "=");
	if (!(new_env = (char**)malloc(sizeof(char*) * (tab_2d_len(env) + 1))))
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(name2, env[i], ft_strlen(name2)))
			new_env[i] = ft_strdup(env[i]);
		else
			new_env[i] = create_line(name, value);
		i++;
	}
	free(name2);
	new_env[i] = NULL;
	return (new_env);
}

char					**ft_setenv(char *name, char *value, char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	if ((ft_getenv(name, env)) != NULL)
		new_env = change_line(name, value, env);
	else
	{
		if (!(new_env = (char**)malloc(sizeof(char*) * (tab_2d_len(env) + 2))))
			return (NULL);
		while (env[i])
		{
			new_env[i] = ft_strdup(env[i]);
			i++;
		}
		new_env[i] = create_line(name, value);
		new_env[i + 1] = NULL;
	}
	return (new_env);
}

void					ft_prepare_setenv(t_cmd *cmd)
{
	char **new_env;
	char **tenv;

	tenv = ft_var_env(NULL);
	if (ft_ret(cmd))
		return ;
	new_env = ft_setenv(cmd->av[1], cmd->av[2], tenv);
	free_tab_2d(tenv);
	ft_var_env(new_env);
}
