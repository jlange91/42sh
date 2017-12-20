/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebrito <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 15:17:07 by adebrito          #+#    #+#             */
/*   Updated: 2017/12/19 15:18:58 by adebrito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/globbing.h"

static	int 	ft_token_glob(char **pat, int escape, int *ret, int *brac)
{
	if (**pat == '[' && !escape)
		*brac = 1;
	if (**pat == ']' && !escape)
		*brac = 0;
	if (**pat == '-' && !escape)
		*ret = 1;
	if (**pat == '*' && !escape)
	{
		*ret = 0;
		if (!(*brac))
			return (1);
	}
	return (0);
}

static	char	*ft_split_pattern(char **chunk, char **pattern, int *bracket)
{
	int		i;
	int 	escape;
	int		leave;

	i = -1;
	leave = 0;
	while (ft_strlen(*pattern) > 0)
	{
		if (**pattern == '\\')
		{
			escape = 1;
			(*chunk)[++i] = *(*pattern)++;
		}
		if (ft_token_glob(pattern, escape, &leave, bracket))
			break;
		(*chunk)[++i] = *(*pattern)++;
		escape = 0;
	}
	(*chunk)[++i] = '\0';
	if (leave != 0)
		ft_strdel(&(*chunk));
	return (*chunk);
}

static	char	*ft_get_next_pattern(char **pattern, int *star, int *bracket)
{
	char	*chunk;

	if (!(ft_strlen(*pattern) > 0))
		return (NULL);
	chunk = NULL;
	if ((chunk = (char *)malloc(sizeof(char) *
					(ft_strlen(*pattern) + 1))) == NULL)
		return (NULL);
	if (*(pattern[0]) == '*')
	{
		(*pattern)++;
		*star = 1;
	}
	return (ft_split_pattern(&chunk, pattern, bracket));
}

static int		ft_match_split(char *pattern, char *word, char *chunk)
{
	int i;

	i = 0;
	while (i < (int)ft_strlen(word))
	{
		if (ft_match_chunk(chunk, &word, i))
		{
			if (ft_strlen(pattern) == 0 && ft_strlen(word) > 0)
				continue;
			return (ft_returnfree(chunk, ft_match(pattern,word), 'f'));
		}
		i++;
	}
	return (ft_returnfree(chunk, 0, 'f'));
}

int				ft_match(char *pattern, char *word)
{
	char	*chunk;
	int		star;
	int		inbracket;

	star = 0;
	inbracket = 0;
	while (ft_strlen(pattern) > 0)
	{
		if ((chunk = ft_get_next_pattern(&pattern, &star, &inbracket)) == NULL)
			return (0);
		if (star && *chunk == '\0' && *pattern != '*')
			return (ft_returnfree(chunk, 1, 'f'));
		if (star)
			return (ft_match_split(pattern, word, chunk));
		if (ft_match_chunk(chunk, &word, 0))
		{
			free(chunk);
			continue;
		}
		return (ft_returnfree(chunk, 0, 'f'));
	}
	return (ft_strlen(word) == 0);
}
