#include "../../inc/autocompletion.h"
#include "../../inc/globbing.h"

static char	**ft_reset_glob(t_termc *sh, char *line)
{
	char		**tmp_tab;

	tputs(sh->term->upstr, 1, ft_inputstr);
	tputs(sh->term->upstr, 1, ft_inputstr);
	ft_free_dlist(&sh->line); 
	ft_init_console(sh, sh->line);
	tmp_tab = ft_strsplit2(line);
	return (tmp_tab);
}

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

char	*ft_add_backslah(char *tmp, int index)
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
			while (glob->tab_str[i][++j])
			{
				if (glob->tab_str[i][j] == '\\' && !ok)
					ft_fill_back_dlst(sh->line, '\\', 1);
				ft_fill_back_dlst(sh->line, glob->tab_str[i][j], 1);
			}
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
}

void	ft_replace_glob(t_termc *sh, char *str, char **env)
{
	int			k;
	char		**tmp_tab;
	char		*before;

	k = -1;
	tmp_tab = ft_reset_glob(sh, str);
	before = NULL;
	while (tmp_tab[++k])
	{
		if (ft_strchr(tmp_tab[k], '/') != NULL)
			before = ft_replace_with_dir(tmp_tab[k]);
		if (ft_glob_here(tmp_tab[k]))
			ft_replace_now(sh, tmp_tab[k], env, before);
		else
			ft_replace_now_split(sh, tmp_tab[k]);
	}
	ft_free_tab(tmp_tab);
	sh->count_tab = 0;
}

int		ft_can_replace_glob(char *line)
{
	int			i;
	int			flag;
	char		**tmp_tab;

	tmp_tab = ft_strsplit2(line);
	i = -1;
	flag = 0;
	while (tmp_tab[++i])
		if (ft_glob_here(tmp_tab[i]))
			flag = 1;
	ft_free_tab(tmp_tab);
	return (flag);
}
