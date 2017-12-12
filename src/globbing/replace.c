#include "../../inc/globbing.h"
#include "../../inc/sh21.h"
#include "../../inc/line_edition.h"

void	ft_init_escape_tab(char *escape_tab)
{
	escape_tab[0] = '!';
	escape_tab[1] = '"';
	escape_tab[2] = '$';
	escape_tab[3] = '&';
	escape_tab[4] = '\'';
	escape_tab[5] = '(';
	escape_tab[6] = ')';
	escape_tab[7] = '*';
	escape_tab[8] = ',';
	escape_tab[9] = ':';
	escape_tab[10] = ';';
	escape_tab[11] = '<';
	escape_tab[12] = '=';
	escape_tab[13] = '>';
	escape_tab[14] = '?';
	escape_tab[15] = '@';
	escape_tab[16] = '[';
	escape_tab[17] = '\\';
	escape_tab[18] = ']';
	escape_tab[19] = '^';
	escape_tab[20] = '`';
	escape_tab[21] = '{';
	escape_tab[22] = '|';
	escape_tab[23] = '}';
	escape_tab[24] = '\0';
}

/*char	*ft_add_backslah(char *tmp, int index)
{
	char	*word;
	int		i;
	int		j;
	int		one;

	if ((word = (char *)malloc(sizeof(char ) * (ft_strlen(tmp) + 2))) == NULL)
	{
		ft_putendl_fd("Error Malloc", 2);
		return (NULL);
	}
	i = -1;
	j = -1;
	one = 0;
	while (tmp[++i])
	{
		if (j == index - 1 && !one)
		{
			word[++j] = '\\';
			one = 1;
		}
		word[++j] = tmp[i];
	}
	word[++j] = '\0';
	return (word);
}

void	ft_add_slash_if(char *word, int *ok)
{
	char		escape_tab[25];
	int			i;
	int			j;
	char		*tmp;

	ft_init_escape_tab(escape_tab);
	j = -1;
	while (word[++j])
	{
		i = -1;
		while (escape_tab[++i])
		{
			if (word[j] == escape_tab[i])
			{
				tmp = ft_strdup(word);
				free(word);
				word = ft_add_backslah(tmp, j);
				free(tmp);
				*ok = 1;
				return ;
			}
		}
	}
}

static void	ft_replace_now_split(t_termc *sh, char *word)
{
	int	j;

	j = -1;
	while (word[++j])
		ft_fill_back_dlst(sh->line, word[j], 1);
	ft_fill_back_dlst(sh->line, ' ', 1);
}

static void	ft_replace_now(t_termc *sh, char *word, char **env, char *before)
{
	t_glob 		*glob;
	int			i;
	int			j;
	int			ok;
	int			index;

	glob = NULL;
	ok = 0;
	ft_parse_glob(word, &glob, env);
	if (glob->tab_str != NULL)
	{
		i = -1;
		while (glob->tab_str[++i])
		{
			j = -1;
			if (before != NULL)
			{
				index = -1;
				while (before[++index])
					ft_fill_back_dlst(sh->line, before[index], 1);
			}
			ft_add_slash_if(glob->tab_str[i], &ok);
			ft_fill_back_dlst(sh->line, ' ', 1);
			ok = 0;
		}
		ft_free_tab(glob->tab_str);
		if (before != NULL)
			free(before);					// I must free so FREE NO GOOD POSITION !!!!
	}
	else
		ft_replace_now_split(sh, word);
	free(glob);
}

char	*ft_replace_with_dir(char *str)
{
	int		index;
	char	*before;
	char	*after;

	index = 0;
	before = NULL;
	after = NULL;
	after = ft_after_antislash(str, &index);
	free(after);
	before = ft_before_antislash(str,index);
	return (before);
}*/

static void ft_cpy(char *line, t_termc *tsh, int ret)
{
	int i;

	i = 0;
	while (line[i])
	{
		ft_fill_back_dlst(tsh->line, line[i], 1);
		i++;
	}
	if (ret)
		ft_fill_back_dlst(tsh->line, ' ', 1);
}
static char	**ft_reset_glob(t_termc *tsh, char *line)
{
	char		**tmp_tab;

	ft_clean_line(tsh);
	tmp_tab = ft_strsplit2(line);
	return (tmp_tab);
}

void		ft_replace_all(char *line, t_termc *tsh)
{
	int			i;
	char		**tmp_tab;
	char		*tmp;
	// t_shell		sh;

	tmp_tab = ft_reset_glob(tsh, line);
	i = -1;
	while (tmp_tab[++i])
	{
		if (ft_glob_here(tmp_tab[i]))
		{
			tmp = ft_glob(tmp_tab[i]);
			ft_cpy(tmp, tsh, 0);
			free(tmp);
		}
		/*else
		{
			sh.line = ft_strdup(tmp_tab[i]);
			ft_replace(&sh);
			ft_cpy(sh.line, tsh, 1);
			free(sh.line);
		}*/
	}
	ft_free_tab(tmp_tab);
}
