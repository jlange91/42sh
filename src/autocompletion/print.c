/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 18:41:53 by vmartins          #+#    #+#             */
/*   Updated: 2018/03/06 16:30:16 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/autocompletion.h"
#include "../../inc/line_edition.h"

/*
**@function
**@param
**@return
*/

static	void	ft_printcolor(struct stat i_d, struct stat i_s, t_autocompl *d)
{
	if (S_ISDIR(i_d.st_mode) || S_ISDIR(i_s.st_mode))
	{
		ft_putstr(BLUE);
		ft_putstr(d->data);
		ft_putchar('/');
	}
	else if ((S_ISREG(i_d.st_mode) && (i_d.st_mode & 0001))
			|| (S_ISREG(i_s.st_mode) && (i_s.st_mode & 0001)))
	{
		ft_putstr(RED);
		ft_putstr(d->data);
		ft_putchar('*');
	}
	else
		ft_putstr(d->data);
	ft_putstr(RESET);
}

/*
**@function
**@param
**@return
*/

static void		ft_fuck_norm(t_autocompl *begin, struct stat info_data,
		struct stat info_str)
{
	ft_putstr(ORANGE_FRONT);
	ft_putstr(PURPLE_BACK);
	ft_putstr(begin->data);
	ft_putstr(RESET);
	if (S_ISDIR(info_data.st_mode))
		ft_putchar('/');
	else if (S_ISDIR(info_str.st_mode))
		ft_putchar('/');
}

void			ft_display_autocompl(t_autocompl *begin, t_auto *select)
{
	struct stat	info_data;
	struct stat	info_str;
	char		*tmp;
	char		**tab_dir;

	ft_memset(&info_data, 0, sizeof(info_data));
	ft_memset(&info_str, 0, sizeof(info_str));
	stat(begin->data, &info_data);
	tab_dir = ft_strsplit2(select->str);
	if (tab_dir != NULL)
	{
		tmp = ft_strjoin(tab_dir[ft_count_dtab(tab_dir) - 1], begin->data);
		ft_free_tab(tab_dir);
		stat(tmp, &info_str);
	}
	else
	{
		tmp = ft_strjoin(select->str, begin->data);
		stat(tmp, &info_str);
	}
	if (begin == select->current && select->can_print >= 1)
		ft_fuck_norm(begin, info_data, info_str);
	else
		ft_printcolor(info_data, info_str, begin);
	free(tmp);
}

/*
**@function
**@param
**@return
*/

t_var_auto		*ft_init_var_auto(t_auto *select)
{
	t_var_auto	*var;

	var = NULL;
	if ((var = (t_var_auto *)malloc(sizeof(*var))) == NULL)
	{
		ft_putendl_fd("Error malloc", 2);
		return (NULL);
	}
	var->len = 0;
	var->down = 0;
	var->row = select->updaterow - 1;
	var->ttl_jump = select->jump + 1;
	return (var);
}
