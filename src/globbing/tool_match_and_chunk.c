/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_match_and_chunk.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 18:35:27 by vmartins          #+#    #+#             */
/*   Updated: 2018/03/06 16:35:34 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/globbing.h"

t_glob	*ft_free_or_not(char **res, char **s_tab, t_glob *glob, int len)
{
	int i;

	i = 0;
	freeall(NULL, res, s_tab, NULL);
	while (i < len)
	{
		free(glob[i].path);
		i++;
	}
	free(glob);
	return (NULL);
}

void	ft_move_index(char **chunk_orig, int *count, char **tmp_orig, int flag)
{
	char	*chunk;
	char	*tmp;

	if (flag == 1)
	{
		chunk = *chunk_orig;
		chunk++;
		(*count)++;
		*chunk_orig = chunk;
	}
	else if (flag == 2)
	{
		chunk = *chunk_orig;
		tmp = *tmp_orig;
		(*count)++;
		chunk++;
		tmp++;
		*tmp_orig = tmp;
		*chunk_orig = chunk;
	}
}

char	*ft_init_var(int *neg, int *count, int *match, char *word)
{
	char	*tmp;

	*neg = 1;
	*count = 0;
	*match = 0;
	tmp = word;
	return (tmp);
}

int		ft_escape_or_end(char *tmp, char **chunk, int *count, int *escape)
{
	if (ft_strlen(tmp) == 0)
		return (1);
	else if ((*chunk)[0] == '\\' && (*chunk)[1] != '\\')
	{
		ft_move_index(chunk, count, NULL, 1);
		*escape = 1;
	}
	return (0);
}

int		ft_skip_or_leave(char **tmp, char **chunk, int *count, int *escape)
{
	if ((*chunk)[0] == '?' && !(*escape))
	{
		ft_move_index(chunk, count, tmp, 2);
		*escape = 0;
	}
	else if ((*chunk)[0] != (*tmp)[0])
		return (1);
	else
	{
		ft_move_index(chunk, count, tmp, 2);
		*escape = 0;
	}
	return (0);
}
