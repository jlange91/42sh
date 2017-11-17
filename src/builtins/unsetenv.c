/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 18:26:41 by jlange            #+#    #+#             */
/*   Updated: 2017/11/03 18:39:04 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"

static inline int	ft_ret(t_shell *sh)
{
	if (sh->ac < 2)
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

void				ft_prepare_unsetenv(t_shell *sh)
{
	int		i;

	i = 0;
	if (ft_ret(sh))
		return ;
	while (sh->av[++i])
	{
		if (ft_getenv(sh->av[i], sh->env) == NULL)
			continue ;
		sh->env = ft_replace_env(ft_unsetenv(sh->av[i], sh->env), sh->env);
	}
}
