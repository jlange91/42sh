/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 12:27:29 by stvalett          #+#    #+#             */
/*   Updated: 2017/04/07 12:33:11 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# define BUFF_SIZE 11
# define CHAR '\n'

typedef struct	s_b
{
	char		*first;
	int			ret2;
	int			res;
}				t_b;

int				get_next_line(const int fd, char **line);

#endif
