/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 16:44:46 by jlange            #+#    #+#             */
/*   Updated: 2018/01/19 16:45:16 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/quote.h"

static int		backslash_word(char *line, int *count)
{
	if (line[0] != '\\')
		return (0);
	if (line[1] == '\n')
		return (2);
	else
	{
		*count += 1;
		return (1);
	}
}

static void		skip_word(char *line, int *i, int *count)
{
	int ret;

	ret = 0;
	while (line[*i] != ' ' && line[*i] != '\t' && line[*i] != '\n'
			&& line[*i] != '\'' && line[*i] != '"' && line[*i])
	{
		ret = backslash_word(&line[*i], count);
		if (ret > 0)
			*i += 1;
		else
			*count += 1;
		*i += 1;
	}
}

static int		backslash_quote(char *line, char c, int *count)
{
	if (line[0] != '\\' || c == '\'')
		return (0);
	if (line[1] == '\n')
		return (2);
	else if (line[1] == '$' || line[1] == '`' ||
			line[1] == '"' || line[1] == '\\' || line[1] == '\n')
	{
		*count += 1;
		return (1);
	}
	else
		return (0);
}

static void		skip_quote(char *line, int *i, int *count)
{
	int		save;
	char	c;
	int		ret;

	save = *i;
	if (line[*i] == '\'' || line[*i] == '"')
	{
		c = line[*i];
		*i += 1;
		while (line[*i] && line[*i] != c)
		{
			ret = backslash_quote(&line[*i], c, count);
			if (ret > 0)
				*i += 1;
			else
				*count += 1;
			*i += 1;
		}
		*i += (line[*i] == c) ? 1 : 0;
	}
}

int				ft_count_av2(char *line, char **av)
{
	int i;
	int j;
	int count;
	int space;

	count = 0;
	i = 0;
	j = 0;
	space = 0;
	while (line[i])
	{
		i += ft_skip_useless(&line[i]);
		skip_word(line, &i, &count);
		skip_quote(line, &i, &count);
		space = ft_skip_useless(&line[i]);
		if (space > 0 || !line[i])
		{
			av[j] = (char*)malloc(sizeof(char) * (count + 1));
			i += space;
			count = 0;
			j++;
		}
	}
	return (0);
}
