/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 18:49:01 by vmartins          #+#    #+#             */
/*   Updated: 2018/02/15 13:23:29 by adebrito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/line_edition.h"
#include "../../inc/sh21.h"

t_console		*init_console(void)
{
	t_console	*console;

	console = NULL;
	if ((console = (t_console *)malloc(sizeof(t_console))) == NULL)
	{
		return (NULL);
	}
	console->total_line = 0;
	console->char_pos = 0;
	return (console);
}

void			ft_init_termc3(t_termc *tsh)
{
	tsh->color = NULL;
	if (!(tsh->color = (char **)malloc(sizeof(char*) * 7)))
		return ;
	tsh->color[0] = RED;
	tsh->color[1] = BLUE;
	tsh->color[2] = YELLOW;
	tsh->color[3] = PINK;
	tsh->color[4] = GREEN;
	tsh->color[5] = RESET;
	tsh->color[6] = NULL;
	tsh->path = 0;
	tsh->prompt = 1;
	tsh->host = 2;
	tsh->hour = 3;
	tsh->linep = 4;
}

int				ft_check_hist(void)
{
	int			fd;

	fd = 0;
	if ((fd = open(&NAME_HIST[1], O_RDONLY)) < 0)
		return (0);
	return (1);
}
