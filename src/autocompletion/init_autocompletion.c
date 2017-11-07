#include "../../inc/autocompletion.h"

static char	*ft_antislash_here(char *str)
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
        new = ft_antislash_here_bis(i, count, str);
    }
    return (new);
}

char	*ft_new_word_backslash(char *word)
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

void    ft_init_simple_autocompl(t_shell *shell, t_env *env)
{
    char            *pwd;
	char			*backslash;
    int             i;
    DIR             *path;
    struct dirent   *file;

    i = 1;
    pwd = ft_getenv("PWD", env);
    if ((path = opendir(pwd)) != NULL)
    {
        ft_free_autocompletion(&shell->autocompl);
        while ((file = readdir(path)) != NULL)
		{
			if (ft_strchr(file->d_name, '\\') != NULL)
			{
				backslash = ft_new_word_backslash(file->d_name);
                ft_fill_back_autocompl(shell->autocompl, backslash, i++);
				free(backslash);
			}
			else if (file->d_name[0] != '.')
                ft_fill_back_autocompl(shell->autocompl, file->d_name, i++);
		}
        shell->autocompl->current = shell->autocompl->begin;
        closedir(path);
    }
    free(pwd);
}

int    ft_open_and_fill(t_shell *shell, DIR *path, int nbr)
{
    int             i;
    struct dirent   *file;

    i = 1;
    if (nbr == 1)
    {
        ft_free_autocompletion(&shell->autocompl);
        while ((file = readdir(path)) != NULL)
            if (file->d_name[0] != '.')
                ft_fill_back_autocompl(shell->autocompl, file->d_name, i++);
        if (!shell->autocompl->begin)
            shell->auto_active = 0;
        shell->autocompl->current = shell->autocompl->begin;
    }
    else if (nbr == 2)
    {
        ft_free_autocompletion(&shell->autocompl);
        while ((file = readdir(path)) != NULL)
            if (file->d_name[0] != '.')
                ft_fill_back_autocompl(shell->autocompl, file->d_name, i++);
        shell->autocompl->current = shell->autocompl->begin;
    }
    closedir(path);
    return (1);
}

void     ft_init_autocompl_bis(t_shell *shell, char *line_tmp, int *flag, t_env *env)
{
    int     i;
    char    *tmp;
    char    **tab_word;
    DIR *path;

    if ((path = opendir(line_tmp)) != NULL)
        *flag = ft_open_and_fill(shell, path, 1);
    else if ((tab_word = ft_strsplit2(line_tmp)) != NULL)
    {
        i = ft_count_dtab(tab_word) - 1;
        if ((path = opendir(tab_word[i])) != NULL)
            *flag = ft_open_and_fill(shell, path, 2);
        else if ((tmp = ft_antislash_here(tab_word[i])) != NULL)    //Because may be file after is bad
        {
            if ((path = opendir(tmp)) != NULL)
            {
                *flag = ft_open_and_fill(shell, path, 2);
                *flag = 0;
            }
            free(tmp);
        }
        ft_free_tab(tab_word);
    }
    else
        ft_init_simple_autocompl(shell, env);
}

int    	ft_init_autocompl(t_shell *shell, char *line, t_env *env)
{
    char			*line_tmp;
    int             flag;

    flag = 0;
    line_tmp = ft_strdup(line);
    if (line_tmp[ft_strlen(line_tmp) - 1] == ' ')  //RESET IF SPACE
    {
        ft_init_simple_autocompl(shell, env);
        free(line_tmp);
        return (1);
    }
    ft_init_autocompl_bis(shell, line_tmp, &flag, env);
    free(line_tmp);
    return (flag);
}
