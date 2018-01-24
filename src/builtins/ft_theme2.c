/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_theme2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebrito <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 14:51:12 by adebrito          #+#    #+#             */
/*   Updated: 2018/01/22 14:52:18 by adebrito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/built_in.h"
#include "../../inc/sh21.h"
#include "../../inc/line_edition.h"

void	ft_theme_hour(char *str, t_termc *tsh)
{
	if (!ft_strcmp(str, "theme_hour_RED"))
		tsh->hour = 0;
	else if (!ft_strcmp(str, "theme_hour_BLUE"))
		tsh->hour = 1;
	else if (!ft_strcmp(str, "theme_hour_YELLOW"))
		tsh->hour = 2;
	else if (!ft_strcmp(str, "theme_hour_PINK"))
		tsh->hour = 3;
	else if (!ft_strcmp(str, "theme_hour_GREEN"))
		tsh->hour = 4;
	else if (!ft_strcmp(str, "theme_hour_WHITE"))
		tsh->hour = 5;
	else
	{
		ft_putstr_fd("Mauvaise syntax", 2);
		return ;
	}
	ft_putstr(tsh->color[tsh->hour]);
	ft_putstr("Modification couleur hour OK ✔︎");
	ft_putstr(RESET);
}

void	ft_theme_prompt(char *str, t_termc *tsh)
{
	if (!ft_strcmp(str, "theme_prompt_RED"))
		tsh->prompt = 0;
	else if (!ft_strcmp(str, "theme_prompt_BLUE"))
		tsh->prompt = 1;
	else if (!ft_strcmp(str, "theme_prompt_YELLOW"))
		tsh->prompt = 2;
	else if (!ft_strcmp(str, "theme_prompt_PINK"))
		tsh->prompt = 3;
	else if (!ft_strcmp(str, "theme_prompt_GREEN"))
		tsh->prompt = 4;
	else if (!ft_strcmp(str, "theme_prompt_WHITE"))
		tsh->prompt = 5;
	else
	{
		ft_putstr_fd("Mauvaise syntax", 2);
		return ;
	}
	ft_putstr(tsh->color[tsh->prompt]);
	ft_putstr("Modification couleur prompt OK ✔︎");
	ft_putstr(RESET);
}

void	ft_theme_host(char *str, t_termc *tsh)
{
	if (!ft_strcmp(str, "theme_host_RED"))
		tsh->host = 0;
	else if (!ft_strcmp(str, "theme_host_BLUE"))
		tsh->host = 1;
	else if (!ft_strcmp(str, "theme_host_YELLOW"))
		tsh->host = 2;
	else if (!ft_strcmp(str, "theme_host_PINK"))
		tsh->host = 3;
	else if (!ft_strcmp(str, "theme_host_GREEN"))
		tsh->host = 4;
	else if (!ft_strcmp(str, "theme_host_WHITE"))
		tsh->host = 5;
	else
	{
		ft_putstr_fd("Mauvaise syntax", 2);
		return ;
	}
	ft_putstr(tsh->color[tsh->host]);
	ft_putstr("Modification couleur host OK ✔︎");
	ft_putstr(RESET);
}

void	ft_theme_path(char *str, t_termc *tsh)
{
	if (!ft_strcmp(str, "theme_path_RED"))
		tsh->path = 0;
	else if (!ft_strcmp(str, "theme_path_BLUE"))
		tsh->path = 1;
	else if (!ft_strcmp(str, "theme_path_YELLOW"))
		tsh->path = 2;
	else if (!ft_strcmp(str, "theme_path_PINK"))
		tsh->path = 3;
	else if (!ft_strcmp(str, "theme_path_GREEN"))
		tsh->path = 4;
	else if (!ft_strcmp(str, "theme_path_WHITE"))
		tsh->path = 5;
	else
	{
		ft_putstr_fd("Mauvaise syntax", 2);
		return ;
	}
	ft_putstr(tsh->color[tsh->path]);
	ft_putstr("Modification couleur path OK ✔︎");
	ft_putstr(RESET);
}

void	ft_theme_global(char *str, t_termc *tsh)
{
	if (!ft_strcmp(str, "theme_global_RED"))
		change_all_color(tsh, 0);
	else if (!ft_strcmp(str, "theme_global_BLUE"))
		change_all_color(tsh, 1);
	else if (!ft_strcmp(str, "theme_global_YELLOW"))
		change_all_color(tsh, 2);
	else if (!ft_strcmp(str, "theme_global_PINK"))
		change_all_color(tsh, 3);
	else if (!ft_strcmp(str, "theme_global_GREEN"))
		change_all_color(tsh, 4);
	else if (!ft_strcmp(str, "theme_global_WHITE"))
		change_all_color(tsh, 5);
	else
	{
		ft_putstr_fd("Mauvaise syntax", 2);
		return ;
	}
	ft_putstr(tsh->color[tsh->path]);
	ft_putstr("Modification couleur global OK ✔︎");
	ft_putstr(RESET);
}
