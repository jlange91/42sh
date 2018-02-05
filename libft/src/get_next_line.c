/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 11:02:47 by stvalett          #+#    #+#             */
/*   Updated: 2018/01/24 18:54:46 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

static int		ft_multi_fd(t_line **list, t_line **current, const int fd)
{
	t_line		*tmp;

	if (*list == NULL)
	{
		if (((*list) = (t_line *)malloc(sizeof(t_line))) == NULL)
			return (1);
		(*list)->fd = fd;
		(*list)->ret = 0;
		(*list)->next = NULL;
	}
	tmp = *list;
	while (tmp->fd != fd)
	{
		if (tmp->next == NULL)
		{
			ft_multi_fd(&(tmp->next), current, fd);
			return (0);
		}
		tmp = tmp->next;
	}
	*current = tmp;
	return (0);
}

static void		ft_del_multi_fd(t_line **list, t_line *current)
{
	t_line		*tmp;

	ft_memdel((void **)&current->next);
	tmp = *list;
	if (*list == current)
	{
		*list = (*list)->next;
		free(current);
	}
	else
	{
		while (tmp->next != current)
			tmp = tmp->next;
		tmp->next = current->next;
		free(current);
	}
}

static int		ft_multi_gnl(char **line, char *buff, int size, int *len)
{
	char		*tmp;

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

static int		ft_read_file(char **line, t_line *current, int *len)
{
	char		*tmp;

	if ((tmp = ft_memchr(current->first, CHAR, current->ret)) == NULL)
	{
		if ((ft_multi_gnl(line, current->first, current->ret, len)) == 1)
			return (-1);
		current->ret = 0;
		current->first = NULL;
	}
	else
	{
		if ((ft_multi_gnl(line, current->first, tmp - current->first, len))
				== 1)
			return (-1);
		current->ret = current->ret - (tmp + 1 - current->first);
		current->first = tmp + 1;
		return (1);
	}
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static t_line	*list;
	t_line			*current;
	int				ret;
	int				res;
	int				len;

	len = -1;
	if (line == NULL || (ft_multi_fd(&list, &current, fd)) == 1)
		return (-1);
	if (current->ret != 0)
	{
		if ((res = ft_read_file(line, current, &len)) == 1)
			return (res);
	}
	while ((ret = read(fd, current->buff, BUFF_SIZE)) > 0)
	{
		current->ret = ret;
		current->first = current->buff;
		if ((res = ft_read_file(line, current, &len)) == 1)
			return (res);
	}
	ft_del_multi_fd(&list, current);
	if (ret == -1)
		return (-1);
	return (len != -1);
}
