/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 09:06:57 by vmartins          #+#    #+#             */
/*   Updated: 2017/11/22 13:31:01 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	color(mode_t mode)
{
	S_ISBLK(mode) ? ft_putstr(RED) : NULL;
	S_ISCHR(mode) ? ft_putstr(BLU) : NULL;
	S_ISDIR(mode) ? ft_putstr(CYN) : NULL;
	S_ISFIFO(mode) ? ft_putstr(WHT) : NULL;
	S_ISLNK(mode) ? ft_putstr(MAG) : NULL;
	S_ISSOCK(mode) ? ft_putstr(GRN) : NULL;
}

void	ft_putab_inline(char **content)
{
	struct stat s;
	int			i;

	i = 0;
	while (content[i])
	{
		lstat(content[i], &s);
		color(s.st_mode);
		ft_putstr(content[i]);
		ft_putstr(RESET);
		if (content[i + 1])
			ft_putstr(" ");
		i++;
	}
}

int		ft_putc(int c)
{
	write(1, &c, 1);
	return (1);
}
