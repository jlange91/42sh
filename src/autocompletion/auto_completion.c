/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 10:23:22 by stvalett          #+#    #+#             */
/*   Updated: 2017/11/16 13:10:16 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/autocompletion.h"
#include "../../inc/globbing.h"
#include "../../inc/line_edition.h"

void    ft_ajuste_and_fill_line(t_termc *tsh, char *data, char *before, int ret)
{
	int         i;

	free(tsh->autoc->str);
	ft_clean_line(tsh);
	tsh->key_tab = 0;
	tsh->autoc->str = ft_strdup(data);
	i = -1;
	if (ret)
		while (before[++i])
			push_backdlst(tsh->line, before[i], i + 2);
	i = -1;
	while (data[++i])
		push_backdlst(tsh->line, data[i], i + 2);
	ft_check_is_dir(tsh);
}

int		ft_findword(t_termc *tsh, char *data, char *before, char *after)
{
	if (ft_count(tsh->autoc) == 1)
	{
		if (ft_strncmp(after, data, ft_strlen(after)) == 0)
		{
			(before == NULL) ? ft_ajuste_and_fill_line(tsh, data, NULL, 0) :
			ft_ajuste_and_fill_line(tsh, data, before, 1);
			return (1);
		}
	}
	else
	{
		if (ft_strcmp(after, data) == 0)
		{
			(before == NULL) ? ft_ajuste_and_fill_line(tsh, data, NULL, 0) :
			ft_ajuste_and_fill_line(tsh, data, before, 1);
			return (1);
		}
	}
	return (0);
}

void    ft_addslash(t_termc *tsh, char **after, char *before)
{
	char		*res;
	char        **tab_word;

	if (ft_dir_or_not(tsh->autoc->str)
			&& tsh->autoc->str[ft_strlen(tsh->autoc->str) - 1] != '/')
		tsh->autoc->str = ft_free_join(tsh->autoc->str, "/", 'L');
	res = ft_strjoin(before, *after);
	if (res)
	{
		tab_word = ft_strsplit2(res);
		if (ft_dir_or_not(tab_word[ft_count_dtab(tab_word) - 1]))
			*after = ft_free_join(*after, "/", 'L');
		ft_free_tab(tab_word);
		free(res);
	}
}

void	ft_autocompletion_bis(t_termc *tsh)
{
	char        *before;
	char        *after;
	int 		limit;
	t_autocompl *begin;

	limit = 0;
	after = ft_after_antislash(tsh->autoc->str, &limit);
	before = ft_strndup(tsh->autoc->str, limit);
	ft_addslash(tsh, &after, before);
	begin = tsh->autoc->current;
	while (begin)
	{
		if (ft_findword(tsh, begin->data, NULL, tsh->autoc->str) ||
				(after != NULL && ft_findword(tsh, begin->data, before, after)))
		{
			tsh->auto_active = 0;
			if (ft_count(tsh->autoc) == 1)// If One word in list , don't display
				tsh->multiauto_active = 0;
			break;
		}
		begin = begin->next;
	}
	free(before);
	free(after);
}

/*
 * * HEART FUNCTION AUTOCOMPLETION
 * *VARIABLE : tsh->auto_active or multiauto_atcive if is active display word
 *
 *  We reset all variable we need, transform list to str, add / in shell line if is shell
 *  line is dir,fill list autocompletion initial current directory or open directory with shell line,
 *  if shell line look like same word in list autocompletion, we fill in new list from
 *  ft_fill_same_word.
 */

void    ft_autocompletion(t_lineterm *end, t_termc *tsh)
{
	(void)end;
	tsh->autoc->arrow = 0;
	if (ft_reset(tsh))
		return ;
	else
	{
		tsh->autoc->str = ft_to_str(tsh);
		ft_replace_all(tsh->autoc->str, tsh);
		free(tsh->autoc->str);
		tsh->autoc->str = ft_to_str(tsh);
		ft_check_is_dir(tsh);
		tsh->auto_active = ft_init_autocompl(tsh, tsh->autoc->str);
		tsh->multiauto_active = ft_fill_same_word(tsh);
		if (tsh->autoc->current && tsh->autoc->str)
			ft_autocompletion_bis(tsh);
		else
			tsh->auto_active = 0;
		if (tsh->repl)
		{
			tsh->auto_active = 0;
			tsh->multiauto_active = 0;
		}
	}
}
