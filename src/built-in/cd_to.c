#include "../../inc/built_in.h"
#include "../../inc/env_term.h"
#include "../../inc/sh21.h"

void	ft_error_of_cd(char *elem, int error)
{
	if (error == 1)
	{
		ft_putstr_fd("\ncd: ", 2);
		ft_putstr_fd("no such file or directory: ", 2);
		ft_putstr_fd(elem, 2);
	}
	else if (error == 2)
	{
		ft_putstr_fd("\ncd: ", 2);
		ft_putstr_fd("permission denied: ", 2);
		ft_putstr_fd(elem, 2);
	}
	else if (error == 3)
	{
		ft_putstr_fd("\ncd: ", 2);
		ft_putstr_fd("not a directory:  ", 2);
		ft_putstr_fd(elem, 2);
	}
}

int		find_error(char *elem)
{
	struct stat s;
	int			i;
	i = lstat(elem, &s);
	if (i == 0 && (access(elem, R_OK) == -1))
		return (2);
	else if (i == 0 && S_ISDIR(s.st_mode) == 0)
		return (3);
	return (1);
}

void	cd_to_dir(char *dir, t_env *env)
{
	char	*tmp;

	if (dir[0] == '.' && ft_strlen(dir) == 1)
		return ;
	early_test(env);
	if (find_var("PWD", env) == NULL && env->line_env != NULL)
	{
		ft_go_to_home(env);
		return ;
	}
	(dir[0] != '$') ? tmp = new_path(dir, env) : NULL;
	if (dir[0] == '$')
	{
		dir = ft_strsub(dir, 1, ft_strlen(dir));
		if (chdir(find_var(dir, env)) == -1)
		{
			free(dir);
			ft_error_of_cd(dir, find_error(dir));
			ft_go_to_home(env);
			return ;
		}
		tmp = ft_strdup(find_var(dir, env));
		free(dir);
	}
	else if(fast_test(dir, tmp) == 1)
		return ;
	permute(tmp, env);
}
