#include "../../inc/sh21.h"

void    ft_free_hash(void)
{
    t_shell *sh;
    int i;
    int j;

    i = 0;
    j = 0;
    sh = ft_ret_sh(NULL);
    while (i < SIZEH)
    {
        if (sh->hash[i].cmd)
            free(sh->hash[i].cmd);
        if (sh->hash[i].path)
            free(sh->hash[i].path);
        if (sh->hash[i].next)
            ft_putendl("ntm");
        i++;
    }
}

int		ft_fill_hash(char *name, char *path)
{
	t_shell *sh;
	DIR		*dir;

	if (access(path, F_OK | X_OK) == 0 && !(dir = opendir(path)))
	{
		sh = ft_ret_sh(NULL);
		ft_add_hash(name, path);
		return (1);
	}
	else
		return (0);
}

static inline char		**fill_path(char **env)
{
	char	**path;
	int		i;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (!ft_strncmp("PATH=", env[i], ft_strlen("PATH=")))
		{
			path = ft_strsplit(&env[i][5], ':');
			return (path);
		}
		i++;
	}
	return (NULL);
}

int		search_hash(char **av, char **env)
{
    t_shell *sh;
	char	**path;
	char	*l_path;
	int		i;

	i = 0;
	if (ft_return_hash(av[0]))
        return (1);
    sh = ft_ret_sh(NULL);
	path = fill_path(env);
	while (path && path[i])
	{
		l_path = ft_replace_line(path[i], "/", av[0]);
		if (ft_fill_hash(av[0], l_path) == 1)
		{
            free(l_path);
            free_tab_2d(path);
            return (1);
		}
		free(l_path);
		i++;
	}
	free_tab_2d(path);
	return (0);
}