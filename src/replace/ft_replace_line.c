/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 18:22:46 by jlange            #+#    #+#             */
/*   Updated: 2017/11/03 18:24:35 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"

static inline void		fill_collins(char *str1, char *str2, int *j)
{
	int i;

	i = 0;
	if (str1)
	{
		while (str1[i])
		{
			str2[*j] = str1[i];
			i++;
			*j += 1;
		}
		i = 0;
	}
}

char					*ft_replace_line(char *str1, char *value, char *str2)
{
	char	*line;
	int		len;
	int		j;

	j = 0;
	len = (str1) ? ft_strlen(str1) : 0;
	len += (value) ? ft_strlen(value) : 0;
	len += (str2) ? ft_strlen(str2) : 0;
	line = (char*)malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	fill_collins(str1, line, &j);
	fill_collins(value, line, &j);
	fill_collins(str2, line, &j);
	line[j] = 0;
	return (line);
}
