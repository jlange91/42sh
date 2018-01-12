#include "../../inc/autocompletion.h"

static char    *ft_slash_here_bis(int limit, int len, char *str)
{
	char	*new;
	int     j;

	if ((new = (char *)malloc(sizeof(char) *
					((ft_strlen(str) - len) + 1))) == NULL)
	{
		ft_putendl_fd("error malloc", 2);
		return (NULL);
	}
	j = -1;
	while (str[++j])
	{
		if (j == limit)
		{
			if (j == 0)
			{
				new[j] = str[j];
				j++;
			}
			break;
		}
		new[j] = str[j];
	}
	new[j] = '\0';
	return (new);
}

static char	*ft_slash_here(char *str)
{
	char	*new;
	int		i;
	int     count;

	new = NULL;
	count = 0;
	i = ft_strlen(str) - 1;
	if (str[i] != '/')
	{
		while (str[i] && str[i] != '/')
		{
			if (i == 0)
				return (new);
			count++;
			i--;
		}
		new = ft_slash_here_bis(i, count, str);
	}
	return (new);
}

static int    ft_open_and_fill(t_termc *tsh, DIR *path, int nbr)
{
	int             i;
	struct dirent   *file;

	i = 1;
	ft_free_autocompletion(&tsh->autoc);
	while ((file = readdir(path)) != NULL)
		if (file->d_name[0] != '.' && file->d_name[1] != '.')
			ft_fill_back_autocompl(tsh->autoc, file->d_name, i++);
	if (!tsh->autoc->begin && nbr == 1)
		tsh->auto_active = 0;
	tsh->autoc->current = tsh->autoc->begin;
	closedir(path);
	return (1);
}

static void     ft_split(t_termc *tsh, char *line, int *flag)
{
	int     i;
	char    *tmp;
	char    **tab_word;
	DIR *path;

	if ((path = opendir(line)) != NULL)
		*flag = ft_open_and_fill(tsh, path, 1);
	else if ((tab_word = ft_strsplit2(line)) != NULL)
	{
		i = ft_count_dtab(tab_word) - 1;
		if ((path = opendir(tab_word[i])) != NULL)
			*flag = ft_open_and_fill(tsh, path, 2);
		else if ((tmp = ft_slash_here(tab_word[i])) != NULL)    //Because may be file after is bad
		{
			if ((path = opendir(tmp)) != NULL)
			{
				*flag = ft_open_and_fill(tsh, path, 2);
				*flag = 0;
			}
			free(tmp);
		}
		ft_free_tab(tab_word);
	}
	else
		ft_init_simple_autocompl(tsh);
}

int    	ft_init_autocompl(t_termc *tsh, char *line)
{
	int             flag;

	flag = 0;
	if (line[ft_strlen(line) - 1] == ' ')  //RESET IF SPACE
	{
		ft_init_simple_autocompl(tsh);
		return (1);
	}
	ft_split(tsh, line, &flag);
	return (flag);
}
