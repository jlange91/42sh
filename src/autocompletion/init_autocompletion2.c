#include "../../inc/autocompletion.h"

void    ft_init_autocompl_binary(t_shell *shell, t_env *env)
{
	int             i;
	char			**dtab;
	char			*path;
	DIR             *dir;
	struct dirent   *file;

	path = ft_getenv("PATH", env);
	if (path != NULL)
	{
		dtab = ft_strsplit(path, ':');
		i = -1;
		while (dtab[++i])
		{
			if ((dir = opendir(dtab[i])) != NULL)
			{
				while ((file = readdir(dir)) != NULL)
					if (file->d_name[0] != '.')
						ft_fill_back_autocompl(shell->autocompl_binary, file->d_name, i + 2);
				closedir(dir);
			}
		}
		free(path);
		ft_free_tab(dtab);
	}
}
