/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 12:28:27 by stvalett          #+#    #+#             */
/*   Updated: 2017/12/12 12:20:13 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

static int	multi_gnl(char **line, char *buff, int size, int *len)
{
	char	*tmp;

	if (*len == -1)
	{
		if ((*line = (char *)malloc(sizeof(char) * size + 1)) == NULL)
			return (1);
		ft_memcpy(*line, buff, size);
		*len = size;
		(*line)[size] = '\0';
	}
	else
	{
		if ((tmp = (char *)malloc(sizeof(char) * *len + size + 1)) == NULL)
			return (1);
		ft_memcpy(tmp, *line, *len);
		ft_memcpy(tmp + *len, buff, size);
		*len = *len + size;
		tmp[*len] = '\0';
		free(*line);
		*line = tmp;
	}
	return (0);
}

static int	read_file(char **line, char **first, int *len, int *ret)
{
	char *tmp;

	if ((tmp = ft_memchr(*first, CHAR, *ret)) == NULL)
	{
		if ((multi_gnl(line, *first, *ret, len)) == 1)
			return (-1);
		*ret = 0;
		*first = NULL;
	}
	else
	{
		if ((multi_gnl(line, *first, tmp - (*first), len)) == 1)
			return (-1);
		*ret = *ret - (tmp + 1 - (*first));
		*first = (tmp + 1);
		return (1);
	}
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	static t_b	tab;
	char		*buff;
	int			ret;
	int			len;

	len = -1;
	if (tab.ret2 != 0)
		if ((tab.res = read_file(line, &tab.first, &len, &tab.ret2)) == 1)
			return (tab.res);
	if ((buff = (char *)malloc(sizeof(char) * BUFF_SIZE + 1)) == NULL)
		return (-1);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		tab.first = buff;
		if ((tab.res = read_file(line, &tab.first, &len, &ret)) == 1)
		{
			tab.ret2 = ret;
			free(buff);
			return (tab.res);
		}
	}
	free(buff);
	if (ret == -1)
		return (-1);
	return (len != -1);
}
