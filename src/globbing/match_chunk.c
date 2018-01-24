/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_chunk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 18:12:44 by stvalett          #+#    #+#             */
/*   Updated: 2018/01/19 18:14:55 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/globbing.h"

static void	ft_is_neg(char **chunk, int *neg)
{
	char	*tmp;

	tmp = *chunk;
	tmp++;
	if (*tmp == '^')
	{
		tmp++;
		*neg = 0;
	}
	*chunk = tmp;
}

static int	ft_found_between(char *chunk, char *lo, char *hi, int *count)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = chunk;
	while (tmp[i] && tmp[i] != ']')
	{
		if (tmp[i] == '-')
		{
			(*count)++;
			*lo = tmp[i - 1];
			*hi = (!(tmp[i + 1] == '\\')) ? tmp[i + 1] : tmp[i + 2];
			return (1);
		}
		i++;
	}
	return (0);
}

static int	ft_end_between(char **chunk_orig, int match, int neg, int *count)
{
	char	*chunk;

	chunk = *chunk_orig;
	if (match != neg)
		return (0);
	if (neg == 0)
		(*count)++;
	if (chunk[0] != ']')
		while (ft_strlen(chunk) > 0)
		{
			if (chunk[0] == ']')
			{
				chunk++;
				break ;
			}
			chunk++;
		}
	*chunk_orig = chunk;
	return (1);
}

static void	ft_between(char **chunk, int *match, char *tmp, int *count)
{
	char	l;
	char	h;

	while (ft_strlen(*chunk) > 0)
	{
		if (!ft_found_between(*chunk, &l, &h, count))
		{
			l = (*chunk)[0];
			h = l;
		}
		if ((*chunk)[0] == ']')
		{
			(*chunk)++;
			break ;
		}
		if (l <= tmp[0] && tmp[0] <= h)
		{
			(*count)++;
			*match = 1;
			break ;
		}
		(*chunk)++;
	}
}

int			ft_match_chunk(char *chunk, char **word, int i)
{
	char	*tmp;
	int		count;
	int		match;
	int		neg;
	int		escape;

	escape = 0;
	tmp = ft_init_var(&neg, &count, &match, *word) + i;
	while (ft_strlen(chunk) > 0)
	{
		if (ft_escape_or_end(tmp, &chunk, &count, &escape))
			return (0);
		else if (chunk[0] == '[' && !escape)
		{
			ft_is_neg(&chunk, &neg);
			ft_between(&chunk, &match, &tmp[0], &count);
			if (!ft_end_between(&chunk, match, neg, &count))
				return (0);
		}
		else if (ft_skip_or_leave(&tmp, &chunk, &count, &escape))
			return (0);
	}
	*word = *word + i + count;
	return (1);
}
