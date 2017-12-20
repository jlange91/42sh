/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 18:26:41 by jlange            #+#    #+#             */
/*   Updated: 2017/12/20 17:11:00 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"

static inline int	ft_ret(t_cmd *cmd)
{
	if (cmd->ac < 2)
	{
		ft_putstr_fd("unsetenv: Too few arguments.\n", 2);
		ft_singleton(1, 1);
		return (1);
	}
	return (0);
}

static inline char	**fill_new_env(char **env, char *name, int i, int j)
{
	char	**new_env;

	new_env = (char**)malloc(sizeof(char*) * (tab_2d_len(env)));
	if (new_env == NULL)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(name, env[i], ft_strlen(name)))
		{
			new_env[j] = ft_strdup(env[i]);
			i++;
			j++;
		}
		else
			i++;
	}
	new_env[j] = NULL;
	return (new_env);
}

char				**ft_unsetenv(char *name, char **env)
{
	char	**new_env;
	char	*name2;

	if (ft_getenv(name, env) == NULL)
		return (ft_cp_env(env));
	name2 = ft_strjoin(name, "=");
	new_env = fill_new_env(env, name2, 0, 0);
	free(name2);
	return (new_env);
}

void				ft_prepare_unsetenv(t_cmd *cmd)
{
	int		i;

	i = 0;
	if (ft_ret(cmd))
		return ;
	while (cmd->av[++i])
	{
		if (ft_getenv(cmd->av[i], cmd->env) == NULL)
			continue ;
		cmd->env = ft_replace_env(ft_unsetenv(cmd->av[i], cmd->env), cmd->env);
	}
	if (!ft_strcmp(cmd->av[0], "unset"))
	{
		i = 0;
		while (cmd->av[++i])
		{
			if (ft_getenv(cmd->av[i], cmd->var) == NULL)
				continue ;
			cmd->var = ft_replace_env(ft_unsetenv(cmd->av[i], cmd->var), cmd->var);
		}
	}
}
