/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 18:06:14 by jlange            #+#    #+#             */
/*   Updated: 2017/11/16 14:50:34 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"
#include "../../inc/ft_perror.h"

static inline void	errno_error(int error)
{
	char **tab;

	tab = (char**)malloc(sizeof(char*) * 26);
	tab[25] = NULL;
	if (error <= 25)
		fill_error_one(tab);
	else if (error <= 50)
		fill_error_two(tab);
	else if (error <= 75)
		fill_error_three(tab);
	else if (error <= 100)
		fill_error_four(tab);
	else
		fill_error_five(tab);
	ft_putstr_fd(tab[(error - 1) % 25], 2);
	free_tab_2d(tab);
}

void				ft_perror(char *str, int error, char *str2)
{
	int		i;

	i = 0;
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	if (error > 0 && error <= 102)
		errno_error(error);
	else
		ft_putstr_fd("Undefined error.\n", 2);
	if (str2)
	{
		write(2, ": ", 2);
		ft_putstr_fd(str2, 2);
	}
	else
		write(2, ".", 1);
	write(2, "\n", 1);
}
