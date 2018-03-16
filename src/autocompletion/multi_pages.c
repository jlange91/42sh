/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pages.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 18:25:50 by vmartins          #+#    #+#             */
/*   Updated: 2018/01/24 18:14:17 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/autocompletion.h"
#include "../../inc/line_edition.h"

/*
**@function
**@param
**@return
*/

static	void	ft_print_page(t_termc *tsh, t_auto *select, t_autocompl *begin)
{
	int			i;

	i = 0;
	while (++i <= select->pages)
	{
		tsh->autoc->jump = select->row;
		if (select->nbr_word >= select->current->index)
		{
			ft_diff_print(select, begin, i, 2);
			break ;
		}
		else if (select->nbr_word * (i + 1) >= select->current->index
				&& select->pages > 1
				&& select->nbr_word * select->pages >= select->current->index)
		{
			while (begin && begin->index < select->nbr_word * i)
				begin = begin->next;
			begin = begin->next;
			ft_diff_print(select, begin, i + 1, 2);
			break ;
		}
	}
}

/*
**@function
**@param
**@return
*/

static	void	what_pages(t_termc *tsh, t_auto *select, int *ecrase, int *e_s)
{
	int			i;

	i = 0;
	while (++i <= select->pages)
	{
		tsh->autoc->jump = select->row;
		if (select->nbr_word >= select->current->index)
		{
			*ecrase = i;
			*e_s = 0;
			break ;
		}
		else if (select->nbr_word * (i + 1) >= select->current->index
				&& select->pages > 1
				&& select->nbr_word * select->pages >= select->current->index)
		{
			*ecrase = i + 1;
			*e_s = 0;
			break ;
		}
	}
}

/*
**@function
**@param
**@return
*/

static	void	ft_clscreen(t_auto *select, t_termc *tsh, int *ecrase, int *e_s)
{
	int			row;

	tputs(tgoto(tgetstr("cm", NULL), 0, select->row + 4), 1, ft_inputstr);
	row = select->row + 4;
	while (row--)
		tputs(tsh->term->upstr, 1, ft_inputstr);
	what_pages(tsh, select, ecrase, e_s);
}

/*
**@function
**@param
**@return
*/

int				ft_clean_all_letter(int i, int res)
{
	static int	ret;
	static int	count;

	if (i == -1 && res == -1)
	{
		ret = -1;
		count = 0;
	}
	if (i == 0 && ret == -1 && count++ > 1)
		ret = res;
	else if (i == 0 && ret != res && count > 1)
		ret = -1;
	return (ret);
}

/*
**@function
**@param
**@return
*/

void			ft_mpages(t_auto *select, t_termc *tsh, t_autocompl *begin)
{
	static int	ecrase;
	static int	ecrase_simple;

	ft_clscreen(select, tsh, &ecrase, &ecrase_simple);
	if (ft_clean_all_letter(0, ecrase) != ecrase && ecrase_simple == 0)
		tputs(tsh->term->cdstr, 1, ft_inputstr);
	ft_display_prompt(tsh);
	ft_display_char(tsh->line->begin, tsh);
	tsh->autoc->updaterow = 3;
	ft_print_page(tsh, select, begin);
	if (select->more_pages != 0
			&& select->current->index > select->nbr_word * select->pages)
	{
		ft_clean_all_letter(-1, -1);
		if (ecrase_simple++ < 1)
			tputs(tsh->term->cdstr, 1, ft_inputstr);
		tsh->autoc->jump = select->more_pages;
		while (begin && begin->index <= select->nbr_word * select->pages)
			begin = begin->next;
		ft_diff_print(select, begin, 0, 1);
	}
}
