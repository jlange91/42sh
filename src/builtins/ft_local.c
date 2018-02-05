/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_local.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 14:41:06 by jlange            #+#    #+#             */
/*   Updated: 2018/01/30 15:39:50 by adebrito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"

int		check_local(t_cmd *cmd)
{
	int		i;

	i = 0;
	while (cmd->av[++i])
	{
		if (check_pattern(cmd->av[i]) == 0)
		{
			ft_putstr_fd("setlocal: bad pattern: ", 2);
			ft_putstr_fd(cmd->av[i], 2);
			return (-1);
		}
		else if (cmd->av[i][0] == '=')
		{
			ft_putstr_fd("Error : bad declare write it like %s=%s", 2);
			return (-1);
		}
	}
	return (0);
}

void	exec_local(char *str)
{
	char	**tmp;
	char	*str_tmp;
	int		index;

	index = 0;
	tmp = ft_strsplit(str, '=');
	str_tmp = NULL;
	if (ft_getenv(tmp[0], ft_var_local(NULL)) && !ft_strchr(str, '='))
	{
		ft_putstr(ft_getenv(tmp[0], ft_var_local(NULL)));
		index = 1;
	}
	else if (ft_getenv(tmp[0], ft_var_local(NULL)) != NULL \
			&& ft_strchr(str, '='))
		basic_replace(tmp[0], str, ft_var_local(NULL));
	else if (!tmp[1])
	{
		str_tmp = ft_strjoin(tmp[0], "=");
		ft_var_local(rapid_set(str_tmp, ft_var_local(NULL), 0));
		free(str_tmp);
	}
	else
		ft_var_local(rapid_set(str, ft_var_local(NULL), 0));
	check_env_export(tmp[0], str, index);
	ft_free_tab(tmp);
}

int		go_local(t_cmd *cmd)
{
	int		i;

	i = 0;
	if (check_local(cmd) == -1)
		return (ft_singleton(1, 1));
	while (cmd->av[++i])
		exec_local(cmd->av[i]);
	return (0);
}

char	**init_local(void)
{
	char	**local;

	if (!(local = (char **)malloc(sizeof(char *) * 1)))
		return (NULL);
	local[0] = NULL;
	return (local);
}

void	prepare_setlocal(t_cmd *cmd)
{
	if (cmd->av[1] == NULL)
		ft_display_env(ft_var_local(NULL));
	if (cmd->av[1] != NULL)
		go_local(cmd);
}
