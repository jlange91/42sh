/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 18:42:28 by jlange            #+#    #+#             */
/*   Updated: 2017/12/20 18:55:04 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"
#include "../../inc/built_in.h"

static inline char	*find_value(char *env)
{
	char	*new_env;
	char	*value;
	int		i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	value = ft_itoa(ft_atoi(&env[i + 1]) + 1);
	new_env = ft_strjoin("SHLVL=", value);
	free(value);
	return (new_env);
}

static inline char	**up_sh_lvl(char **env, int i)
{
	char	**new_env;

	if (ft_getenv("SHLVL", env) == NULL)
	{
		new_env = ft_setenv("SHLVL", "1", env);
		return (new_env);
	}
	if (!(new_env = (char**)malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp("SHLVL=", env[i], ft_strlen("SHLVL=")))
			new_env[i] = ft_strdup(env[i]);
		else
			new_env[i] = find_value(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

void				ft_fill_env(t_shell *sh, char **env)
{
	char	pwd[PATH_MAX];
	char	*pwd2;

	sh->env = up_sh_lvl(env, tab_2d_len(env));
	if ((pwd2 = ft_getenv("PWD", env)) == NULL)
	{
		getcwd(pwd, sizeof(pwd));
		sh->env = ft_replace_env(ft_setenv("PWD", pwd, sh->env), sh->env);
		sh->pwd = ft_strdup(pwd);
	}
	else
	{
		sh->pwd = ft_strdup(&pwd2[4]);
		sh->env = ft_replace_env(ft_setenv("PWD", sh->pwd, sh->env), sh->env);
	}
	//sh->var = load_env(sh->env);
}
