#include "../../inc/autocompletion.h"
#include "../../inc/globbing.h"

static char	**ft_reset_glob(t_shell *shell, char *line, t_env *env)
{
	char		**tmp_tab;

	tputs(shell->term->upstr, 1, ft_inputstr);
	tputs(shell->term->upstr, 1, ft_inputstr);
	ft_free_dlist(&shell->line); 
	ft_init_console(shell, shell->line, env);
	tmp_tab = ft_strsplit2(line);
	return (tmp_tab);
}

static void	ft_replace_now(t_shell *shell, char *word, t_env *env)
{
	t_glob 		*glob;
	int			i;
	int			j;

	glob = NULL;
	ft_parse_glob(word, &glob, env);
	if (glob->tab_str != NULL)
	{
		i = -1;
		while (glob->tab_str[++i])
		{
			j = -1;
			while (glob->tab_str[i][++j])
			{
				if (glob->tab_str[i][j] == '\\')
					ft_fill_back_dlst(shell->line, '\\', 1);
				ft_fill_back_dlst(shell->line, glob->tab_str[i][j], 1);
			}
			ft_fill_back_dlst(shell->line, ' ', 1);
		}
		ft_free_tab(glob->tab_str);
	}
	else
	{
		j = -1;
		while (word[++j])
			ft_fill_back_dlst(shell->line, word[j], 1);
		ft_fill_back_dlst(shell->line, ' ', 1);
	}
	free(glob);
}

void	ft_replace_glob(t_shell *shell, char *str, t_env *env)
{
	int			j;
	int			k;
	char		**tmp_tab;

	k = -1;
	tmp_tab = ft_reset_glob(shell, str, env);
	while (tmp_tab[++k])
	{
		if (ft_glob_here(tmp_tab[k]))
			ft_replace_now(shell, tmp_tab[k], env);
		else
		{
			j = -1;
			while (tmp_tab[k][++j])
				ft_fill_back_dlst(shell->line, tmp_tab[k][j], 1);
			ft_fill_back_dlst(shell->line, ' ', 1);
		}
	}
	ft_free_tab(tmp_tab);
	shell->count_tab = 0;
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
