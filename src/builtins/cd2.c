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

static inline void	replace_pwd(void)
{
	char *tmp;
	char **tenv;

	tenv = ft_var_env(NULL);
	tmp = ft_getenv("PWD", tenv);
	if (tmp && tmp[4])
		ft_var_env(ft_replace_env(ft_setenv("OLDPWD", &tmp[4], tenv), tenv));
	tenv = ft_var_env(NULL);
	ft_var_env(ft_replace_env(ft_setenv("PWD", ft_var_pwd(NULL), tenv), tenv));
}

void				ft_cd_l(char *path)
{
	char *curpath;

	if (path[0] == '/')
		curpath = ft_strdup(path);
	else
	{
		curpath = ft_strjoin(ft_var_pwd(NULL), "/");
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

	ft_var_pwd(ft_replace_str(curpath, ft_var_pwd(NULL)));
	replace_pwd();
}

void				ft_cd_p(char *path)
{
	char curpath[PATH_MAX];

	if (chdir(path) == -1)
	{
		ft_chdir_error(path);
		ft_singleton(1, 1);
		return ;
	}
	getcwd(curpath, PATH_MAX);
	ft_var_pwd(ft_replace_str(ft_strdup(curpath), ft_var_pwd(NULL)));
	replace_pwd();
}
