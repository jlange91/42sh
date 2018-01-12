#include "../../inc/autocompletion.h"

static char	*ft_new_word_backslash(char *word)
{
	char	*new;
	int		i;
	int		j;

	if ((new = (char *)malloc(sizeof(char) * (ft_strlen(word) + 2))) == NULL)
	{
		ft_putendl_fd("Error malloc", 2);
		return (NULL);
	}
	i = -1;
	j = -1;
	while (word[++i])
	{
		if (word[i] == '\\')
			new[++j] = '\\';
		new[++j] = word[i];
	}
	new[++j] = '\0';
	return (new);
}

void    ft_init_simple_autocompl(t_termc *tsh)
{
	char			*backslash;
	int             i;
	DIR             *path;
	struct dirent   *file;

	i = 1;
	if ((path = opendir(".")) != NULL)
	{
		ft_free_autocompletion(&tsh->autoc);
		while ((file = readdir(path)) != NULL)
		{
			if (ft_strchr(file->d_name, '\\') != NULL)
			{
				backslash = ft_new_word_backslash(file->d_name);
				ft_fill_back_autocompl(tsh->autoc, backslash, i++);
				free(backslash);
			}
			else if (file->d_name[0] != '.' && file->d_name[1] != '.')
				ft_fill_back_autocompl(tsh->autoc, file->d_name, i++);
		}
		tsh->autoc->current = tsh->autoc->begin;
		closedir(path);
	}
}
