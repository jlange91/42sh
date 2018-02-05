/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_from_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 18:39:56 by stvalett          #+#    #+#             */
/*   Updated: 2018/01/24 18:41:17 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include <fcntl.h>

int		ft_count_from_file(char *path)
{
	int		fd;
	int		count;
	int		ret;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = NULL;
	count = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		count++;
		free(line);
	}
	close(fd);
	return (count);
}
