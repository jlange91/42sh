/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 18:25:16 by jlange            #+#    #+#             */
/*   Updated: 2017/12/20 17:04:26 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"
#include "../../inc/built_in.h"

static inline void	replace_pwd(t_cmd *cmd)
{
	char *tmp;

	tmp = ft_getenv("PWD", cmd->env);
	if (tmp && tmp[4])
		cmd->env = ft_replace_env(ft_setenv("OLDPWD", &tmp[4], cmd->env),
				cmd->env);
	cmd->env = ft_replace_env(ft_setenv("PWD", cmd->pwd, cmd->env), cmd->env);
}

void				ft_cd_l(t_cmd *cmd, char *path)
{
	char *curpath;

	if (path[0] == '/')
		curpath = ft_strdup(path);
	else
	{
		curpath = ft_strjoin(cmd->pwd, "/");
		curpath = ft_replace_str(ft_strjoin(curpath, path), curpath);
	}
	curpath = ft_replace_str(ft_remove_useless_path(curpath), curpath);
	if (chdir(curpath) == -1)
	{
		free(curpath);
		ft_chdir_error(path);
		ft_singleton(1, 1);
		return ;
	}
	cmd->pwd = ft_replace_str(curpath, cmd->pwd);
	replace_pwd(cmd);
}

void				ft_cd_p(t_cmd *cmd, char *path)
{
	char curpath[PATH_MAX];

	if (chdir(path) == -1)
	{
		ft_chdir_error(path);
		ft_singleton(1, 1);
		return ;
	}
	getcwd(curpath, PATH_MAX);
	cmd->pwd = ft_replace_str(ft_strdup(curpath), cmd->pwd);
	replace_pwd(cmd);
}
