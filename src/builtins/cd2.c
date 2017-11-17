/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 18:25:16 by jlange            #+#    #+#             */
/*   Updated: 2017/11/16 13:25:50 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"
#include "../../inc/built_in.h"

static inline void	replace_pwd(t_shell *sh)
{
	char *tmp;

	tmp = ft_getenv("PWD", sh->env);
	if (tmp && tmp[4])
		sh->env = ft_replace_env(ft_setenv("OLDPWD", &tmp[4], sh->env),
				sh->env);
	sh->env = ft_replace_env(ft_setenv("PWD", sh->pwd, sh->env), sh->env);
}

void				ft_cd_l(t_shell *sh, char *path)
{
	char *curpath;

	if (path[0] == '/')
		curpath = ft_strdup(path);
	else
	{
		curpath = ft_strjoin(sh->pwd, "/");
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
	sh->pwd = ft_replace_str(curpath, sh->pwd);
	replace_pwd(sh);
}

void				ft_cd_p(t_shell *sh, char *path)
{
	char curpath[PATH_MAX];

	if (chdir(path) == -1)
	{
		ft_chdir_error(path);
		ft_singleton(1, 1);
		return ;
	}
	getcwd(curpath, PATH_MAX);
	sh->pwd = ft_replace_str(ft_strdup(curpath), sh->pwd);
	replace_pwd(sh);
}
