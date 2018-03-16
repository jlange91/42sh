/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 11:01:18 by vmartins          #+#    #+#             */
/*   Updated: 2017/04/05 12:05:08 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

# define BUFF_SIZE 1
# define CHAR	'\n'

typedef	struct			s_line
{
	int					fd;
	int					ret;
	char				*first;
	char				buff[10000000];
	struct s_line		*next;
}						t_line;

int						get_next_line(const int fd, char **line);

#endif
