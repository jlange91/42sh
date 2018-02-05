/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_globbing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 15:48:28 by stvalett          #+#    #+#             */
/*   Updated: 2018/01/30 12:25:34 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/globbing.h"
#include "../../inc/sh21.h"
#include "../../inc/line_edition.h"

static	inline	void	ft_cpy_simple(char *data, t_termc *tsh)
{
	int					i;

	i = 0;
	while (data[i])
	{
		if (tsh->line->lnk_before)
			ft_insert_dlnk(tsh->line->end, tsh, data[i], 1);
		else
			push_backdlst(tsh->line, data[i], 1);
		i++;
	}
	tsh->repl = 1;
	tsh->keyflag->k_tab = 0;
	ft_strdel(&data);
}

static	inline	char	*ft_get_word(t_termc *tsh, int i)
{
	char				*word;
	t_lineterm			*end;

	word = NULL;
	if ((word = (char *)malloc(sizeof(char) * (i + 1))) == NULL)
		return (NULL);
	end = find_cursor(tsh->line->end, 0);
	i = 0;
	while (end && end->c != ' ' && end->index != 0)
	{
		word[i] = end->c;
		i++;
		end = end->prev;
	}
	word[i] = '\0';
	ft_reverse(word);
	if (!ft_glob_here(word) && !ft_strchr(word, '$'))
	{
		free(word);
		return (NULL);
	}
	return (word);
}

static	inline	void	ft_repl_expand(char *replace, char *word, t_termc *tsh)
{
	int					i;
	t_lineterm			*begin;

	tsh->keyflag->k_tab = 0;
	tsh->repl = 1;
	if (ft_strcmp(replace, word) != 0 && ft_strlen(replace) > 0)
	{
		begin = find_cursor(tsh->line->end, 0);
		i = ft_strlen(word) - 1;
		while (begin)
		{
			if (i > -1 && begin->c == word[i] && begin)
			{
				i--;
				begin->under = 1;
				begin = begin->prev;
			}
			else
				break ;
		}
		ft_cut_line(begin, tsh);
		ft_cpy_simple(replace, tsh);
	}
	else
		ft_strdel(&replace);
}

static	inline	void	ft_repl_glob(char *word, t_termc *tsh)
{
	int					i;
	char				*glob;
	t_lineterm			*begin;

	i = 0;
	begin = find_cursor(tsh->line->end, 0);
	i = ft_strlen(word) - 1;
	if ((glob = ft_glob(word)) == NULL)
		return ;
	while (begin)
	{
		if (i > -1 && begin->c == word[i] && begin)
		{
			i--;
			begin->under = 1;
			begin = begin->prev;
		}
		else
			break ;
	}
	ft_cut_line(begin, tsh);
	ft_cpy_simple(glob, tsh);
}

void					ft_replace_glob_exp(t_termc *tsh, t_lineterm *endt)
{
	int					i;
	char				*word;
	t_lineterm			*end;
	t_shell				*sh;

	tsh->line->last = (!endt->next) ? 1 : 0;
	end = find_cursor(tsh->line->end, 0);
	i = 0;
	while (end && end->c != ' ' && end->index != 0)
	{
		i++;
		end = end->prev;
	}
	if ((word = ft_get_word(tsh, i)) == NULL)
		return ;
	if (ft_glob_here(word))
		ft_repl_glob(word, tsh);
	else if (ft_strchr(word, '$'))
	{
		sh = ft_ret_sh(NULL);
		sh->line = ft_strdup(word);
		ft_replace(sh);
		ft_repl_expand(sh->line, word, tsh);
	}
	free(word);
}
