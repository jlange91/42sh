/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 10:23:22 by vmartins          #+#    #+#             */
/*   Updated: 2018/01/23 17:19:11 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/autocompletion.h"
#include "../../inc/globbing.h"
#include "../../inc/line_edition.h"

/*
**@function We fill with word before and data
**@param	1 = struct t_termc *tsh
**			2 = data is word in list autoc
**			3 = b is word before "/"
**			4 = ret is flag for know if before != NULL
**@return
*/

static	void	ft_fill_line(t_termc *tsh, char *data, char *b, int ret)
{
	int	i;

	free(tsh->autoc->str);
	ft_clean_line(tsh);
	tsh->keyflag->k_tab = 0;
	tsh->autoc->str = ft_strdup(data);
	i = -1;
	if (ret)
		while (b[++i])
			push_backdlst(tsh->line, b[i], i + 2);
	i = -1;
	while (data[++i])
		push_backdlst(tsh->line, data[i], i + 2);
	ft_check_is_dir(tsh);
}

/*
**@function	If one word in list autoc, we found with strncmp
**			If match with after and data, we fill to line
**@param	1 = struct t_termc *tsh
**			2 = data is word in list autoc
**			3 = b is word before "/"
**			4 = a is word after "/"
**@return	1 is TRUE , 0 is FALSE
*/

static	int		ft_findword(t_termc *tsh, char *data, char *b, char *a)
{
	if (ft_count(tsh->autoc) == 1)
	{
		if (ft_strncmp(a, data, ft_strlen(a)) == 0)
		{
			(b == NULL) ? ft_fill_line(tsh, data, NULL, 0) :
				ft_fill_line(tsh, data, b, 1);
			return (1);
		}
	}
	else
	{
		if (ft_strcmp(a, data) == 0)
		{
			(b == NULL) ? ft_fill_line(tsh, data, NULL, 0) :
				ft_fill_line(tsh, data, b, 1);
			return (1);
		}
	}
	return (0);
}

/*
**@function	If the string is dir, we add "/"
**@param	1 = struct t_termc *tsh
**			2 = a == word after "/"
**			3 = b == word before "/"
**@return
*/

static	void	ft_addslash(t_termc *tsh, char **a, char *b)
{
	char		*res;
	char		**tab_word;

	if (ft_dir_or_not(tsh->autoc->str)
			&& tsh->autoc->str[ft_strlen(tsh->autoc->str) - 1] != '/')
		tsh->autoc->str = ft_free_join(tsh->autoc->str, "/", 'L');
	res = ft_strjoin(b, *a);
	if (res)
	{
		tab_word = ft_strsplit2(res);
		if (ft_dir_or_not(tab_word[ft_count_dtab(tab_word) - 1]))
			*a = ft_free_join(*a, "/", 'L');
		ft_free_tab(tab_word);
		free(res);
	}
}

/*
**@function	Find_word and replace to line
**@param     struct t_termc *tsh
**@return
**@comment	before = word before "/"
**			after = word after "/"
*/

static	void	ft_autocompletion_bis(t_termc *tsh)
{
	char		*before;
	char		*after;
	int			limit;
	t_autocompl	*begin;

	limit = 0;
	after = ft_after_antislash(tsh->autoc->str, &limit);
	before = ft_strndup(tsh->autoc->str, limit);
	ft_addslash(tsh, &after, before);
	begin = tsh->autoc->current;
	while (begin)
	{
		if (ft_findword(tsh, begin->data, NULL, tsh->autoc->str)\
				|| (after && ft_findword(tsh, begin->data, before, after)))
		{
			tsh->auto_active = 0;
			if (ft_count(tsh->autoc) == 1)
				tsh->multiauto_active = 0;
			break ;
		}
		begin = begin->next;
	}
	free(before);
	free(after);
}

/*
**@function	First replace Glob and expansion and find word for autoc
**			if tsh->autoc_active || tsh->multiautoc_active || tsh->repla
**			== 0 NO PRINT AUTOC
**@param	1 = where is cursor, 2 = struct t_termc *tsh
**@return
*/

void			ft_autocompletion(t_lineterm *end, t_termc *tsh)
{
	tsh->autoc->arrow = 0;
	if (ft_reset(tsh))
		return ;
	else
	{
		ft_replace_glob_exp(tsh, end);
		ft_check_is_dir(tsh);
		tsh->autoc->str = ft_remove_char(ft_to_str(tsh, 0), '\\');
		if (ft_not_str(tsh->autoc->str, tsh))
			return ;
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
		if (!tsh->auto_active && !tsh->multiauto_active)
			tsh->keyflag->k_tab = 0;
	}
}
