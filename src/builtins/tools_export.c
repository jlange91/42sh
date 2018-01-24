/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 14:25:57 by adebrito          #+#    #+#             */
/*   Updated: 2018/01/22 14:31:11 by adebrito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"

void	ft_display_export(char **var)
{
	int	i;

	i = -1;
	while (var[++i])
	{
		ft_putstr("export ");
		ft_putendl(var[i]);
	}
}

int		only_p(t_cmd *cmd)
{
	int i;

	i = 0;
	while (cmd->av[++i])
	{
		if (ft_strcmp(cmd->av[i], "-p"))
			return (0);
	}
	ft_display_export(ft_var_var(NULL));
	return (1);
}

int		check_pattern(char *str)
{
	int		i;
	char	**tmp;

	i = -1;
	tmp = ft_strsplit(str, '=');
	if (tmp[0])
	{
		while (tmp[0][++i])
		{
			if (ft_isalpha(tmp[0][i]) == 0)
			{
				ft_free_tab(tmp);
				return (0);
			}
		}
		ft_free_tab(tmp);
	}
	return (1);
}

void	add_each(t_cmd *cmd, int i, char *tmp)
{
	char	*str;

	str = NULL;
	if (ft_getenv(tmp, ft_var_var(NULL)) == NULL)
	{
		str = ft_strdup(cmd->av[i]);
		ft_var_var(rapid_set(str, ft_var_var(NULL), 0));
		if (ft_getenv(tmp, ft_var_local(NULL)) != NULL)
		{
			replace_elem(tmp, str, ft_var_local(NULL));
			free(str);
		}
		else
			ft_var_env(rapid_set(str, ft_var_env(NULL), 1));
	}
	else if (ft_getenv(tmp, ft_var_var(NULL)) != NULL)
	{
		replace_elem(tmp, cmd->av[i], ft_var_var(NULL));
		replace_elem(tmp, cmd->av[i], ft_var_env(NULL));
		if (ft_getenv(tmp, ft_var_local(NULL)) != NULL)
			replace_elem(tmp, cmd->av[i], ft_var_local(NULL));
	}
}

void	basic_replace(char *compare, char *input, char **env)
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
}
