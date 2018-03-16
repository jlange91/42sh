/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 18:42:28 by jlange            #+#    #+#             */
/*   Updated: 2018/02/13 11:16:02 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"
#include "../../inc/built_in.h"

static	inline	void	init_without_env(int *test)
{
	char	**tmp;

	*test = 1;
	if ((tmp = (char **)malloc(sizeof(char *) * 2)) == NULL)
		exit(1);
	tmp[0] = ft_strdup("SHLVL=1");
	tmp[1] = NULL;
	ft_var_var(load_env(tmp));
	ft_free_tab(tmp);
}

static	inline	char	*find_value(char *env)
{
	char				*new_env;
	char				*value;
	int					i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	value = ft_itoa(ft_atoi(&env[i + 1]) + 1);
	new_env = ft_strjoin("SHLVL=", value);
	free(value);
	return (new_env);
}

static	inline	char	**up_sh_lvl(char **env, int i, int *test)
{
	char				**new_env;

	if (ft_getenv("SHLVL", env) == NULL)
	{
		init_without_env(test);
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

void					ft_fill_env(char **env)
{
	char				pwd[PATH_MAX];
	char				*pwd2;
	char				**tenv;
	int					test;

	test = 0;
	ft_var_env(up_sh_lvl(env, tab_2d_len(env), &test));
	tenv = ft_var_env(NULL);
	if (!test)
		ft_var_var(load_env(tenv));
	ft_var_local(init_local());
	if ((pwd2 = ft_getenv("PWD", env)) == NULL)
	{
		getcwd(pwd, sizeof(pwd));
		ft_var_env(ft_replace_env(ft_setenv("PWD", pwd, tenv), tenv));
		ft_var_pwd(ft_strdup(pwd));
	}
	else
	{
		ft_var_env(ft_replace_env(ft_setenv("PWD", &pwd2[4], tenv), tenv));
		ft_var_pwd(ft_strdup(&pwd2[4]));
	}
}
