/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebrito <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 16:16:40 by adebrito          #+#    #+#             */
/*   Updated: 2017/11/22 13:31:19 by adebrito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void				suspended(void)
{
	t_select	*s;
	char		cp[2];

	s = keep_term(NULL);
	s->default_term.c_lflag |= (ICANON | ECHO);
	tcsetattr(0, 0, &(s->default_term));
	ft_putstr_fd(tgetstr("te", NULL), 2);
	ft_putstr_fd(tgetstr("ve", NULL), 2);
	signal(SIGTSTP, SIG_DFL);
	cp[0] = s->default_term.c_cc[VSUSP];
	cp[1] = 0;
	ioctl(0, TIOCSTI, cp);
}

void					abort_term(void)
{
	t_select	*s;

	s = keep_term(NULL);
	s->default_term.c_lflag |= (ICANON | ECHO);
	tcsetattr(0, 0, &(s->default_term));
	ft_putstr_fd(tgetstr("te", NULL), 2);
	ft_putstr_fd(tgetstr("ve", NULL), 2);
	exit(EXIT_FAILURE);
}

static	void			continue_term(int flag)
{
	t_select	*s;

	s = keep_term(NULL);
	if (flag == 1)
	{
		tputs(tgetstr("cl", NULL), 1, ft_putc);
		ft_print_all(&s, 0, 0);
		return ;
	}
	else
	{
		ft_init_term(&s);
		ft_putstr_fd("ft_select restored, press an arrow key", 2);
	}
}

static	void			sig_handler(int signo)
{
	if (signo == SIGWINCH)
	{
		continue_term(1);
		return ;
	}
	if (signo == SIGCONT)
		continue_term(2);
	else if (signo == SIGTSTP)
		suspended();
	else
		abort_term();
}

int						ft_signal(void)
{
	if (signal(SIGCONT, sig_handler) == SIG_ERR)
		ft_putstr_fd("\ncan't catch SIGCONT\n", 2);
	if (signal(SIGTSTP, sig_handler) == SIG_ERR)
		ft_putstr_fd("\ncan't catch SIGTSTP\n", 2);
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		ft_putstr_fd("\ncan't catch SIGTSTP\n", 2);
	if (signal(SIGWINCH, sig_handler) == SIG_ERR)
		ft_putstr_fd("\ncan't catch SIGWINCH\n", 2);
	return (0);
}
