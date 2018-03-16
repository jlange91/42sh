/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 19:03:31 by vmartins          #+#    #+#             */
/*   Updated: 2018/01/22 19:04:34 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/line_edition.h"
#include "../../inc/built_in.h"

static	void	ft_print_hour(void)
{
	time_t		time_sec;
	struct tm	now;
	char		*tmp;

	time(&time_sec);
	now = *localtime(&time_sec);
	ft_putstr(" [");
	tmp = ft_itoa(now.tm_hour);
	if (ft_strlen(tmp) == 1)
		ft_putchar('0');
	free(tmp);
	ft_putnbr(now.tm_hour);
	ft_putchar(':');
	tmp = ft_itoa(now.tm_min);
	if (ft_strlen(tmp) == 1)
		ft_putchar('0');
	free(tmp);
	ft_putnbr(now.tm_min);
	ft_putchar(':');
	tmp = ft_itoa(now.tm_sec);
	if (ft_strlen(tmp) == 1)
		ft_putchar('0');
	free(tmp);
	ft_putnbr(now.tm_sec);
	ft_putstr("] ");
}

static	int		ft_print_current_work(void)
{
	ft_putendl(ft_var_pwd(NULL));
	ft_putstr(RESET);
	return (ft_strlen(ft_var_pwd(NULL)));
}

void			ft_display_prompt(t_termc *tsh)
{
	int			len;
	char		host[256];

	len = 10;
	gethostname(host, sizeof(host));
	len += ft_strlen(host);
	ft_putendl("");
	ft_putstr(tsh->color[tsh->hour]);
	if (ft_singleton(0, 0))
		ft_putstr("😡");
	else
		ft_putstr("😃");
	ft_print_hour();
	ft_putstr(tsh->color[tsh->host]);
	ft_putstr(host);
	ft_putstr(tsh->color[tsh->path]);
	ft_putchar(' ');
	len += ft_print_current_work();
	tsh->len_prompt = len + 3;
}
