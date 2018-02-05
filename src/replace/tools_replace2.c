/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_replace2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 16:00:29 by stvalett          #+#    #+#             */
/*   Updated: 2018/01/22 16:00:53 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/globbing.h"
#include "../../inc/sh21.h"
#include "../../inc/line_edition.h"

void		ft_add_space(char **line, char **s_line, char *word)
{
	int		i;
	long	c;
	char	*str;

	if (!(*line) || !(*s_line) || !word)
		return ;
	str = ft_strjoin(*s_line, word);
	if (str != NULL)
	{
		i = 0;
		c = 0;
		while (str[i] && str[i] != ' ' && str[i] != '\n')
			i++;
		while (str[i] && (str[i] == ' ' || str[i] == '\n'))
		{
			c = (long)str[i];
			*line = ft_free_join(*line, (char *)&c, 'L');
			i++;
		}
		ft_strdel(&(*s_line));
		if (str && str[i] != 0)
			*s_line = ft_strdup(&str[i]);
		if (str)
			free(str);
	}
}

void		ft_join_all(char *word, char **line_tmp, int ret)
{
	*line_tmp = (*line_tmp == NULL) ? ft_strdup(word) :
		ft_free_join(*line_tmp, word, 'L');
	if (ret && word)
		free(word);
}
