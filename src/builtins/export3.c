/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 16:18:32 by adebrito          #+#    #+#             */
/*   Updated: 2017/12/20 17:06:33 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"

int		info(char *elem, struct stat s)
{
	if (S_ISDIR(s.st_mode) || access(elem, X_OK) == -1)
		return (-1);
	else
		return (-2);
}

int		find_bin(char **path_tab, char *elem)
{
	int			i;
	struct stat s;

	i = -1;
	lstat(elem, &s);
	if (ft_strchr(elem, '/'))
		return (info(elem, s));
	if (path_tab)
		while (path_tab[++i])
		{
			path_tab[i] = ft_free_join(path_tab[i],
					ft_strjoin("/", elem), 'B');
			if (!access(path_tab[i], X_OK))
				return (i);
		}
	return (-1);
}

int		search_exec(char **str, char **t_tmp, char *elem)
{
	int		i;
	char	**path_tab;
	int		info;

	i = -1;
	path_tab = ft_strsplit(ft_getenv("PATH", ft_var_env(NULL)), ':');
	if ((info = find_bin(path_tab, t_tmp[1])) >= 0)
		elem = ft_strdup(path_tab[info]);
	if (info == -2)
		elem = ft_strdup(t_tmp[1]);
	ft_free_tab(path_tab);
	if ((*str)[ft_strlen(*str) - 1] == '=')
		return (-1);
	while ((*str)[++i] && info != -1)
	{
		if ((*str)[i] == '=')
		{
			free(*str);
			*str = ft_free_join(t_tmp[0], ft_free_join("=", elem, 'R'), 'R');
			return (1);
		}
	}
	return (-1);
}

void	export_flag_b(t_cmd *cmd, int i)
{
	char	**tmp;
	char	*str;

	str = NULL;
	tmp = ft_strsplit(cmd->av[i], '=');
	search_exec(&cmd->av[i], tmp, str);
	if (tmp[0])
	{
		if (ft_getenv(tmp[0], cmd->var) == NULL)
		{
			str = ft_strdup(cmd->av[i]);
			cmd->var = rapid_set(str, cmd->var, 0);
			ft_var_env(rapid_set(str, ft_var_env(NULL), 1));
		}
		else if (ft_getenv(tmp[0], cmd->var) != NULL)
		{
			replace_elem(tmp[0], cmd->av[i], cmd->var);
			replace_elem(tmp[0], cmd->av[i], ft_var_env(NULL));
		}
		ft_free_tab(tmp);
	}
}

int		check_correct_arg(t_cmd *cmd, int i)
{
	char	**tmp;
	char	*str;
	int		nb;

	str = NULL;
	nb = -1;
	tmp = ft_strsplit(cmd->av[i], '=');
	if (tmp[0])
	{
		if (tab_2d_len(tmp) == 2)
		{
			nb = search_exec(&cmd->av[i], tmp, str);
			if (nb == -1)
				ft_putstr_fd("command not found", 2);
		}
		else
			ft_putendl_fd("Error : bad declaration write it like %s=%s", 2);
		ft_free_tab(tmp);
	}
	return (nb);
}
