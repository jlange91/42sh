#include "../../inc/globbing.h"

int  ft_count_file(char *str)
{
	int             count;
	DIR             *path;
	struct dirent   *file;

	count = 0;
	if ((path = opendir(str)) != NULL)
	{
		while ((file = readdir(path)) != NULL)
			count++;
		closedir(path);
	}
	return (count);
}

void	ft_save_word(t_glob *glob, char **str, int len)
{
	int	i;
	struct stat	info;

	i = 0;
	while (i < len)
	{
		ft_memset(&info, 0, sizeof(info));
		if (stat(glob[i].path, &info) != -1)
		{
			if (glob[i].path != NULL && *str == NULL)
				*str = ft_strjoin(glob[i].path, " ");
			else if (glob[i].path != NULL && *str != NULL)
			{
				*str = ft_free_join(*str, glob[i].path, 'L');
				*str = ft_free_join(*str, " ", 'L');
			}
		}
		i++;
	}
}

void	ft_freeall_glob(char *pwd, char **res, char **s_tab, t_glob *glob)
{
    int i;

    if (glob != NULL)
    {
        i = 0;
        while (i < glob->len)
        {
            free(glob[i].path);
            i++;
        }
        free(glob);
    }
	if (pwd != NULL)
		free(pwd);
	if (res != NULL)
		ft_free_tab(res);
	if (s_tab != NULL)
		ft_free_tab(s_tab);
}

char	*ft_add_b_slash(char *file)
{
	char		escape_tab[25];
	char		*new;
	int			j;
	int			k;
	int			i;

	if ((new = (char *)malloc(sizeof(char) * (ft_strlen(file) * 2)+ 1)) == NULL)
		return (NULL);
	ft_init_escape_tab(escape_tab);
	j = -1;
	k = -1;
	while (file[++j])
	{
		i = -1;
		while (escape_tab[++i])
			if (file[j] == escape_tab[i + 1])
				new[++k] = '\\';
		new[++k] = file[j];
	}
	new[++k] = '\0';
	return (new);
}

char	**ft_add_slash(char *path, char c)
{
	int 	i;
	int		j;
	int 	len;
	char	**s_tab;
	char	**slash_tmp;

	len = (path[0] == '/') ? ft_count_word(path, '/') + 1 :
        ft_count_word(path, '/');
	if ((s_tab = (char **)malloc(sizeof(char *) * (len + 1))) == NULL)
		return (NULL);
	slash_tmp = ft_strsplit(path, '/');
	i = -1;
	j = -1;
	if (path[0] == '/')
		s_tab[++j] = ft_strdup("/");
	while (slash_tmp[++i])
	{
        s_tab[++j] = ((c != '/' && i == len - 1) ||
            (path[0] == '/' && i == len - 2 && c != '/')) ?
            ft_strdup(slash_tmp[i]) : ft_strjoin(slash_tmp[i], "/");
	}
	s_tab[++j] = NULL;
	ft_free_tab(slash_tmp);
	return (s_tab);
}
