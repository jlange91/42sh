/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_to_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 15:54:50 by stvalett          #+#    #+#             */
/*   Updated: 2018/01/30 14:40:11 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/globbing.h"
#include "../../inc/sh21.h"
#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"

static	void	ft_get_hist(char *word, char **line_tmp)
{
	int			i;
	char		*str;
	t_termc		*tsh;

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
	if (str && ft_strcmp(str, word))
		tsh->repl = 1;
	(!str) ? ft_join_all(word, line_tmp, 0) : ft_join_all(str, line_tmp, 1);
	ft_free_t_dlst(&tsh->line);
}

static	void	ft_findok(char *word, t_shell *sh, char **line_tmp, int flag)
{
	char		*glob;

	if (flag == 0)
	{
		sh->line = ft_strdup(word);
		ft_replace(sh);
		ft_join_all(sh->line, line_tmp, 1);
	}
	else if (flag == 1)
	{
		((glob = ft_glob(word)) != NULL) ? ft_join_all(glob, line_tmp, 1) :
			ft_join_all(word, line_tmp, 0);
	}
	else if (flag == 2)
		ft_get_hist(word, line_tmp);
}

static	int		ft_check_tilde(char *word)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!ft_strchr(word, '~'))
		return (0);
	while (word[i])
	{
		if (word[i] == ' ')
			count = 0;
		if (count > 1)
			return (1);
		if (word[i] == '~')
			count++;
		i++;
	}
	return (0);
}

static	char	*ft_split_res(char **save_line, t_shell *sh, char **new_tab)
{
	char		*line_tmp;
	int			i;

	i = 0;
	line_tmp = NULL;
	while (new_tab[i])
	{
		if ((ft_strchr(new_tab[i], '$') || ft_strchr(new_tab[i], '~')) &&
				!ft_glob_here(new_tab[i]) && !ft_check_tilde(new_tab[i]))
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

void			ft_result_replace(t_shell *sh)
{
	char		*save_line;
	char		**new_tab;
	t_termc		*tsh;

	if (!sh->line)
		return ;
	tsh = ft_ret_tsh(NULL);
	new_tab = ft_strsplit2(sh->line);
	save_line = ft_strdup(sh->line);
	if (tsh->save_line != NULL)
		free(tsh->save_line);
	tsh->save_line = ft_strdup(sh->line);
	free(sh->line);
	sh->line = ft_split_res(&save_line, sh, new_tab);
	if (tsh->repl)
	{
		tsh->replace = ft_strdup(sh->line);
		free(sh->line);
	}
	if (save_line)
		free(save_line);
	ft_free_tab(new_tab);
}
