/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 15:38:35 by stvalett          #+#    #+#             */
/*   Updated: 2018/01/23 15:39:43 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"
#include "../../inc/quote.h"

int					ft_inputstr(int c)
{
	write(0, &c, 1);
	return (0);
}

size_t				get_columns(void)
{
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	return (w.ws_col);
}

int					ft_reset_line(t_termc *tsh)
{
	int				len;

	ft_putchar('\n');
	len = ft_ret_down(-1);
	while (len-- && !tsh->quotes)
		tputs(tsh->term->dostr, 1, ft_inputstr);
	ft_ret_down(0);
	tsh->autoc->finish = 1;
	tsh->keyflag->cl = 0;
	if (tsh->auto_active || tsh->multiauto_active)
	{
		free(tsh->autoc->str);
		tsh->autoc->str = NULL;
		ft_free_autocompletion(&tsh->autoc);
		tsh->auto_active = 0;
		tsh->multiauto_active = 0;
	}
	tputs(tsh->term->vestr, 1, ft_inputstr);
	return (0);
}

int					ft_save_line(t_termc *tsh)
{
	t_lineterm		*tmp;

	tputs(tsh->term->clrstr, 1, ft_inputstr);
	ft_ret_down(0);
	tsh->keyflag->cl = 1;
	tmp = tsh->line->begin;
	tmp = ft_ps1(tmp);
	if (tsh->line_dup->begin)
		ft_free_dlist(&tsh->line_dup);
	while (tmp)
	{
		push_backdlst(tsh->line_dup, tmp->c, 1);
		tmp = tmp->next;
	}
	return (0);
}

char				*ft_to_str(t_termc *tsh, int q)
{
	char			*str;
	int				i;
	t_lineterm		*tmp;

	if ((tmp = tsh->line->begin) == NULL)
		return (NULL);
	if (!(str = (char *)malloc(sizeof(*str) * ft_count_dlnk(tsh, q) + 1 + q)))
		return (NULL);
	i = 0;
	tmp = (tmp->next && q) ? ft_ps2(tmp) : ft_ps1(tmp);
	while (tmp)
	{
		str[i] = tmp->c;
		i++;
		tmp = tmp->next;
	}
	str[i] = '\0';
	return (str);
}
