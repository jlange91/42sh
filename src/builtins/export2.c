/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 16:13:58 by vmartins          #+#    #+#             */
/*   Updated: 2018/01/25 16:20:49 by vmartins         ###   ########.fr       */
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

void	replace_elem(char *compare, char *input, char **env)
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
	if (ft_getenv(compare, ft_var_env(NULL)) == NULL)
		ft_var_env(rapid_set(input, ft_var_env(NULL), 0));
}

void	export_flagb(t_cmd *cmd, int i)
{
	while (cmd->av[++i])
	{
		if (check_pattern(cmd->av[i]) == 0)
		{
			ft_putstr_fd("export: ", 2);
			ft_putstr_fd(cmd->av[i], 2);
			ft_putendl_fd(": not a valid identifier", 2);
			ft_singleton(1, 1);
			return ;
		}
		else if (!ft_strchr(cmd->av[i], '=') || cmd->av[i][0] == '=')
		{
			ft_putendl_fd("Error : bad declaration write it like %s=%s", 2);
			ft_singleton(1, 1);
			return ;
		}
		else if (check_correct_arg(cmd, i) == -1)
		{
			ft_singleton(1, 1);
			return ;
		}
	}
	i = 1;
	while (cmd->av[++i])
		export_flag_b(cmd, i);
}

void	export_no_eq(t_cmd *cmd, int i)
{
	if (ft_getenv(cmd->av[i], ft_var_local(NULL)) != NULL && \
			ft_getenv(cmd->av[i], ft_var_var(NULL)) == NULL)
	{
		ft_var_var(rapid_set(ft_getenv(cmd->av[i], ft_var_local(NULL)),\
					ft_var_var(NULL), 0));
		ft_var_env(rapid_set(ft_getenv(cmd->av[i], ft_var_local(NULL)),\
					ft_var_env(NULL), 0));
	}
	else if (ft_getenv(cmd->av[i], ft_var_var(NULL)) == NULL \
			&& !ft_strchr(cmd->av[i], '='))
		ft_var_var(rapid_set(ft_strjoin(cmd->av[i], "=''"), \
					ft_var_var(NULL), 1));
	else if (ft_getenv(cmd->av[i], ft_var_var(NULL)) != NULL && \
			!ft_strchr(cmd->av[i], '=') && \
			ft_getenv(cmd->av[i], ft_var_env(NULL)) == NULL)
	{
		if (ft_strchr(ft_getenv(cmd->av[i], ft_var_var(NULL)), '\''))
			ft_var_env(rapid_set(ft_strjoin(cmd->av[i], "="), \
						ft_var_env(NULL), 1));
		else
			ft_var_env(rapid_set(ft_getenv(cmd->av[i], ft_var_var(NULL)), \
						ft_var_env(NULL), 0));
	}
}

int		export_with_eq(t_cmd *cmd, int i)
{
	char	**tmp;
	char	*str;

	str = NULL;
	if (cmd->av[i][0] == '=')
	{
		ft_putendl_fd("Error : bad declaration write it like %s=%s", 2);
		return (1);
	}
	tmp = ft_strsplit(cmd->av[i], '=');
	if (tmp[0])
	{
		add_each(cmd, i, tmp[0]);
		ft_free_tab(tmp);
		return (0);
	}
	return (0);
}
