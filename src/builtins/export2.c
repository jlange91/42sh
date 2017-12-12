/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebrito <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 16:13:58 by adebrito          #+#    #+#             */
/*   Updated: 2017/12/08 16:22:59 by adebrito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"

char	**rapid_set(char *input, char **env, int j)
{
	int		i;
	char	**new_env;

	i = 0;
	if (!(new_env = (char**)malloc(sizeof(char*) * (tab_2d_len(env) + 2))))
		return (0);
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = ft_strdup(input);
	new_env[i + 1] = 0;
	if (j == 1)
		free(input);
	ft_free_tab(env);
	return (new_env);
}

void	replace_elem(char *compare, char *input, char **env, t_shell *sh)
{
	int		i;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(compare, env[i], ft_strlen(compare)) == 0)
		{
			free(env[i]);
			env[i] = ft_strdup(input);
		}
		else if (ft_strncmp(input, env[i], ft_strlen(input)) == 0)
			return ;
	}
	if (ft_getenv(compare, sh->env) == NULL)
		sh->env = rapid_set(input, sh->env, 0);
}

void	export_flagb(t_shell *sh)
{
	int		i;

	i = 1;
	while (sh->av[++i])
	{
		if (ft_strchr(sh->av[i], '=') && ft_strchr(sh->av[i], '-'))
		{
			ft_putendl_fd("bad option -=", 2);
			return ;
		}
		else if (!ft_strchr(sh->av[i], '=') || sh->av[i][0] == '=')
		{
			ft_putstr_fd("Error : bad declaration write it like %s=%s", 2);
			return ;
		}
		else if (check_correct_arg(sh, i) == -1)
			return ;
	}
	i = 1;
	while (sh->av[++i])
		export_flag_b(sh, i);
}

void	export_no_eq(t_shell *sh, int i)
{
	if (ft_getenv(sh->av[i], sh->var) == NULL && !ft_strchr(sh->av[i], '='))
		sh->var = rapid_set(ft_strjoin(sh->av[i], "=''"), sh->var, 1);
	else if (ft_getenv(sh->av[i], sh->var) != NULL && \
			!ft_strchr(sh->av[i], '=') && \
			ft_getenv(sh->av[i], sh->env) == NULL)
		sh->env = rapid_set(ft_strjoin(sh->av[i], "="), sh->env, 1);
}

void	export_with_eq(t_shell *sh, int i)
{
	char	**tmp;
	char	*str;

	str = NULL;
	if (sh->av[i][0] == '=')
	{
			ft_putstr_fd("Error : bad declaration write it like %s=%s", 2);
			return ;
	}
	tmp = ft_strsplit(sh->av[i], '=');
	if (ft_getenv(tmp[0], sh->var) == NULL)
	{
		str = ft_strdup(sh->av[i]);
		sh->var = rapid_set(str, sh->var, 0);
		sh->env = rapid_set(str, sh->env, 1);
	}
	if (ft_getenv(tmp[0], sh->var) != NULL)
	{
		replace_elem(tmp[0], sh->av[i], sh->var, sh);
		replace_elem(tmp[0], sh->av[i], sh->env, sh);
	}
	ft_free_tab(tmp);
}
