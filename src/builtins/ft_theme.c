/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_theme.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 14:50:41 by vmartins          #+#    #+#             */
/*   Updated: 2018/01/22 14:44:15 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/built_in.h"
#include "../../inc/sh21.h"
#include "../../inc/line_edition.h"

void	change_all_color(t_termc *tsh, int color)
{
	tsh->host = color;
	tsh->hour = color;
	tsh->prompt = color;
	tsh->path = color;
	tsh->linep = color;
}

void	ft_theme_line(char *str, t_termc *tsh)
{
	if (!ft_strcmp(str, "theme_line_RED"))
		tsh->linep = 0;
	else if (!ft_strcmp(str, "theme_line_BLUE"))
		tsh->linep = 1;
	else if (!ft_strcmp(str, "theme_line_YELLOW"))
		tsh->linep = 2;
	else if (!ft_strcmp(str, "theme_line_PINK"))
		tsh->linep = 3;
	else if (!ft_strcmp(str, "theme_line_GREEN"))
		tsh->linep = 4;
	else if (!ft_strcmp(str, "theme_line_WHITE"))
		tsh->linep = 5;
	else
		ft_putstr_fd("Mauvaise syntax", 2);
}

void	show_color(void)
{
	ft_putstr(RED);
	ft_putstr("RED ");
	ft_putstr(BLUE);
	ft_putstr("BLUE ");
	ft_putstr(YELLOW);
	ft_putstr("YELLOW ");
	ft_putstr(PINK);
	ft_putstr("PINK ");
	ft_putstr(GREEN);
	ft_putstr("GREEN ");
	ft_putstr(RESET);
	ft_putstr("WHITE\n");
}

void	show_usage(void)
{
	ft_putstr("Voici les differentes modification que ");
	ft_putendl("vous pouvez effectuer :");
	ft_putstr("⎛  theme_hour_ | theme_prompt_ | theme_path_ | theme_host |");
	ft_putendl(" | theme_line_ | theme_global_ ⎞");
	ft_putstr("Ensuite precisez la couleur comme par exemple : ");
	ft_putstr("theme_hour_GREEN, mettra l'heure en vert");
}

void	ft_theme(t_cmd *cmd, t_termc *tsh)
{
	if (!ft_strcmp(cmd->av[0], "theme"))
	{
		ft_putstr("MODIFIER LES COULEUR DU ");
		ft_putendl("SHELL AVEC CES DIFFERENTES COULEUR :");
		show_color();
		show_usage();
	}
	else
	{
		if (!ft_strncmp(cmd->av[0], "theme_hour_", 11))
			ft_theme_hour(cmd->av[0], tsh);
		else if (!ft_strncmp(cmd->av[0], "theme_prompt_", 13))
			ft_theme_prompt(cmd->av[0], tsh);
		else if (!ft_strncmp(cmd->av[0], "theme_path_", 11))
			ft_theme_path(cmd->av[0], tsh);
		else if (!ft_strncmp(cmd->av[0], "theme_host_", 11))
			ft_theme_host(cmd->av[0], tsh);
		else if (!ft_strncmp(cmd->av[0], "theme_line_", 11))
			ft_theme_line(cmd->av[0], tsh);
		else if (!ft_strncmp(cmd->av[0], "theme_global_", 13))
			ft_theme_global(cmd->av[0], tsh);
		else
			ft_putstr_fd("Mauvaise syntax", 2);
	}
}
