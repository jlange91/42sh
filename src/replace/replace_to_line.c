#include "../../inc/globbing.h"
#include "../../inc/sh21.h"
#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"

static inline int ft_only_space(char *line, char c)
{
	int i;

	i = 0;
	while (line[i] && line[i] == c)
		i++;
	if (line[i] == 0)
		return (1);
	else
		return (0);
}

static inline void ft_get_hist(char *word, char **line_tmp)
{
	int 	i;
	char 	*str;
	t_termc *tsh;

	i = 0;
	tsh = ft_ret_tsh(NULL);
	ft_fill_prompt(tsh->line);
	while (word[i])
	{
		push_backdlst(tsh->line, word[i], 1);
		i++;
	}
	ft_replace_exp_hist(tsh);
	str = ft_to_str(tsh, 0);
	(!str) ? ft_join_all(word, line_tmp, 0) : ft_join_all(str, line_tmp, 1);
	ft_free_dlist(&tsh->line);
}

static inline void ft_findok(char *word, t_shell *sh, char **line_tmp, int flag)
{
	char *glob;

	if (flag == 0)
	{
		sh->line = ft_strdup(word);
		ft_replace(sh);
		(ft_strcmp(sh->line, word) && !ft_only_space(sh->line, ' ')) ?
		ft_join_all(sh->line, line_tmp, 1) : ft_join_all(word, line_tmp, 0);
	}
	else if (flag == 1)
	{
		((glob = ft_glob(word)) != NULL) ? ft_join_all(glob, line_tmp, 1) :
		ft_join_all(word, line_tmp, 0);
	}
	else if (flag == 2)
		ft_get_hist(word, line_tmp);
}

static inline char *ft_split_res(char *save_line, t_shell *sh, char **new_tab)
{
	char 	*line_tmp;
	int 	i;

	i = 0;
	line_tmp = NULL;
	while (new_tab[i])
	{
		if ((ft_strchr(new_tab[i], '$') || ft_strchr(new_tab[i], '~')) &&\
			!ft_glob_here(new_tab[i]))
			ft_findok(new_tab[i], sh, &line_tmp, 0);
		else if (ft_glob_here(new_tab[i]))
			ft_findok(new_tab[i], sh, &line_tmp, 1);
		else if (ft_strchr(new_tab[i], '!') && ft_strlen(new_tab[i]) > 1)
			ft_findok(new_tab[i], sh, &line_tmp, 2);
		else
			ft_join_all(new_tab[i], &line_tmp, 0);
		ft_add_space(&line_tmp, save_line, new_tab[i]);
		i++;
	}
	return (line_tmp);
}

void 	ft_result_replace(t_shell *sh)
{
	char 	*save_line;
	char 	**new_tab;
	t_termc *tsh;

	tsh = ft_ret_tsh(NULL);
	new_tab = ft_strsplit2(sh->line);
	save_line = ft_strdup(sh->line);
	free(sh->line);
	sh->line = ft_split_res(save_line, sh, new_tab);
	if (ft_strlen(sh->line) >= 1)
		ft_add_tmp_history(tsh, sh->line);
	ft_free_tab(new_tab);
	free(save_line);
}
