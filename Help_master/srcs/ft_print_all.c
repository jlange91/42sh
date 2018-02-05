/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebrito <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 10:07:37 by adebrito          #+#    #+#             */
/*   Updated: 2018/01/25 16:24:37 by adebrito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static	void			print_close(t_select **select, int i, char *cap)
{
	t_select	*s;

	s = *select;
	if (s->elem[i].select == 1)
	{
		if ((cap = tgetstr("me", NULL)) == NULL)
			ft_putstr("Cannot set the end of all appearance mode\n");
		else
			tputs(cap, 0, ft_putc);
	}
}

static	void			print_else(t_select **select, int i, char *cap, int len)
{
	t_select	*s;
	struct stat sb;

	s = *select;
	lstat(s->elem[i].str, &sb);
	ft_putstr("    ");
	if (s->elem[i].select == 1)
	{
		if ((cap = tgetstr("mr", NULL)) == NULL)
			ft_putendl("Cannot set reverse video mode");
		else
			tputs(cap, 0, ft_putc);
	}
	color(sb.st_mode);
	ft_putstr(s->elem[i].str);
	ft_putstr(RESET);
	if (s->elem[i].select == 1)
		tputs(tgetstr("me", NULL), 0, ft_putc);
	while (len-- > 0)
		ft_putchar(' ');
	ft_putchar('\n');
}

static	void			print_again(t_select **select, int i, char *cap)
{
	t_select	*s;

	s = *select;
	if (s->elem[i].select == 1)
	{
		if ((cap = tgetstr("mr", NULL)) == NULL)
			ft_putstr("Cannot set reverse video mode\n");
		else
			tputs(cap, 0, ft_putc);
	}
	if ((cap = tgetstr("us", NULL)) == NULL)
		ft_putstr("Cannot set the underline mode\n");
	else
		tputs(cap, 0, ft_putc);
	ft_putstr(s->elem[i].str);
	if ((cap = tgetstr("ue", NULL)) == NULL)
		ft_putstr("Cannot set the end of underline mode\n");
	else
		tputs(cap, 0, ft_putc);
	print_close(select, i, cap);
}

static	void			ft_print2(t_select **select, int i, int col, int tmp)
{
	t_select	*s;
	int			len;

	s = *select;
	tputs(tgoto(tgetstr("cm", NULL), col, tmp), 0, ft_putc);
	len = s->max_strlen - ft_strlen(s->elem[i].str);
	if (i == (s->cursor_line - 1))
	{
		if (i % 4 == 0)
			ft_putstr_fd(RED, 2);
		else if (i % 3 == 0)
			ft_putstr_fd(GRN, 2);
		else if (i % 2 == 1)
			ft_putstr_fd(CYN, 2);
		else if (i % 2 == 0)
			ft_putstr_fd(YEL, 2);
		ft_putstr_fd("  ~> ", 2);
		print_again(select, i, NULL);
		ft_putstr_fd(" <~", 2);
		ft_putstr_fd(RESET, 2);
	}
	else
		print_else(select, i, NULL, len);
}

void					ft_print_all(t_select **select, int i, int col)
{
	t_select	*s;
	int			tmp;
	char		*cap;

	tmp = 0;
	s = *select;
	cap = NULL;
	if (!ft_find_window_len(select))
	{
		ft_putstr_fd("Screen too small", 2);
		return ;
	}
	while (i < s->nb_elem)
	{
		ft_print2(select, i, col, tmp);
		if (tmp >= s->height - 2)
		{
			col += s->max_strlen + 5;
			tmp = -1;
		}
		i++;
		tmp++;
	}
}
