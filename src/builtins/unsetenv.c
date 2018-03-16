/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 18:26:41 by jlange            #+#    #+#             */
/*   Updated: 2018/01/25 18:26:24 by vmartins         ###   ########.fr       */
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
	int		i;

	i = 0;
	if (ft_getenv(name, env) == NULL)
		return (ft_cp_env(env));
	if (ft_strcmp(name, "PATH") == 0)
		ft_reinit_hash();
	name2 = ft_strjoin(name, "=");
	new_env = fill_new_env(env, name2, 0, 0);
	free(name2);
	return (new_env);
}

void				do_unset(t_cmd *cmd)
{
	char	**tvar;
	char	**tlocal;
	int		i;

	tvar = ft_var_var(NULL);
	tlocal = ft_var_local(NULL);
	i = 0;
	while (cmd->av[++i])
	{
		if (ft_getenv(cmd->av[i], tvar) == NULL)
			continue ;
		ft_var_var(ft_replace_env(ft_unsetenv(cmd->av[i], tvar), tvar));
	}
	i = 0;
	while (cmd->av[++i])
	{
		if (ft_getenv(cmd->av[i], tlocal) == NULL)
			continue ;
		ft_var_local(ft_replace_env(ft_unsetenv(cmd->av[i], tlocal), tlocal));
	}
}

void				ft_prepare_unsetenv(t_cmd *cmd)
{
	char	**tenv;
	int		i;

	i = 0;
	if (ft_ret(cmd))
		return ;
	while (cmd->av[++i])
	{
		tenv = ft_var_env(NULL);
		if (ft_getenv(cmd->av[i], tenv) == NULL)
			continue ;
		ft_var_env(ft_replace_env(ft_unsetenv(cmd->av[i], tenv), tenv));
	}
	if (!ft_strcmp(cmd->av[0], "unset"))
		do_unset(cmd);
}
