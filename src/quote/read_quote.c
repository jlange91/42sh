/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 16:47:48 by jlange            #+#    #+#             */
/*   Updated: 2018/01/23 17:44:03 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/quote.h"
#include "../../inc/line_edition.h"

static inline int		ft_fill_prompt_quotes(t_dlst *line, int ret)
{
	char	*str;
	int		i;

	str = NULL;
	if (ret == -1)
		str = "dquote > ";
	else if (ret == -2)
		str = "quote > ";
	else if (ret == -3)
		str = "bquote > ";
	else if (ret == -4)
		str = "> ";
	if (str)
	{
		i = -1;
		while (str[++i])
			push_backdlst(line, str[i], 0);
		return (1);
	}
	return (0);
}

static	inline	int		ft_doublequotes(int ret, int *yes, t_termc *t)
{
	if (ret == 0)
	{
		tputs(t->term->upstr, 1, ft_inputstr);
		*yes = 0;
		return (0);
	}
	else
	{
		ft_free_t_dlst(&t->line);
		ft_fill_prompt_quotes(t->line, ret);
		ft_find_history(t);
		return (1);
	}
}

static	inline	int		ft_s_quote(t_termc *t, int *yes, int *ret, char *tmp)
{
	int					i;
	char				*test;

	i = 0;
	t->quotes = 1;
	while (i < (int)t->console->total_line)
	{
		tputs(t->term->dostr, 1, ft_inputstr);
		i++;
	}
	if (((test = (ft_strchr(tmp, '\\'))) != NULL
				&& (test[ft_strlen(test) - 1] == '\\'
					|| test[ft_strlen(test) - 1] == '\n'))
			&& *ret != -1 && *ret != -2 && *ret != -3)
	{
		*ret = -4;
		*yes = 1;
		ft_free_t_dlst(&t->line);
		ft_fill_prompt_quotes(t->line, *ret);
		tmp = ft_ret_word_quote(&tmp, 0);
		*ret = ft_check_quote(tmp);
		ft_find_history(t);
		return (1);
	}
	return (0);
}

int						ft_line_quotes(t_termc *t)
{
	char			*tmp;
	static int		ret;
	static int		yes;

	if (!t->quotes)
	{
		tmp = ft_to_str(t, 0);
		ret = ft_check_quote(tmp);
		free(tmp);
	}
	if (ret != 0 || yes)
	{
		tmp = ft_to_str(t, 1);
		if (ft_s_quote(t, &yes, &ret, tmp))
			return (1);
		tmp = ft_ret_word_quote(&tmp, 0);
		ret = ft_check_quote(tmp);
		return (ft_doublequotes(ret, &yes, t));
	}
	return (0);
}
