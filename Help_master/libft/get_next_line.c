/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebrito <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 16:02:20 by adebrito          #+#    #+#             */
/*   Updated: 2017/05/22 16:02:21 by adebrito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*find_list(t_list **lst, int fd)
{
	t_list	*list;

	list = *lst;
	if (!list)
	{
		list = ft_lstnew("\0", 1);
		list->content_size = fd;
		*lst = list;
		return (list);
	}
	while (list && list->content_size != (size_t)fd)
		list = list->next;
	if (list)
		return (list);
	list = ft_lstnew("\0", 1);
	list->content_size = fd;
	ft_lstadd(lst, list);
	return (*lst);
}

int		check_all(t_list **lst, char **line)
{
	char	*tmp;
	char	*tmp2;
	t_list	*list;

	list = *lst;
	if ((list->content && ft_strcmp(list->content, "") != 0) &&
			!(ft_strchr(list->content, '\n')))
	{
		*line = ft_strdup(list->content);
		ft_memdel(&list->content);
		return (1);
	}
	if ((list->content && ft_strcmp(list->content, "") != 0) &&
			(tmp = ft_strchr(list->content, '\n')))
	{
		*line = ft_strsub(list->content, 0, tmp - (char*)list->content);
		tmp2 = ft_strdup(tmp + 1);
		ft_memdel(&list->content);
		list->content = tmp2;
		return (1);
	}
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	static t_list	*lst = NULL;
	int				nb;
	t_list			*list;

	if (read(fd, buf, 0) < 0 && (fd < 0))
		return (-1);
	list = find_list(&lst, fd);
	while (list->content && !ft_strchr(list->content, '\n') &&
			(nb = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[nb] = '\0';
		list->content = ft_free_join(list->content, buf, 'L');
	}
	if (check_all(&list, line) == 1)
		return (1);
	return (0);
}
