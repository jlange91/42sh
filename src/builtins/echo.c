/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 18:25:21 by jlange            #+#    #+#             */
/*   Updated: 2017/11/16 13:26:10 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"
#include "../../inc/built_in.h"

static void				fill_sval(int sval[20])
{
	sval[0] = 07;
	sval[1] = 010;
	sval[2] = 128;
	sval[3] = 033;
	sval[4] = 014;
	sval[5] = 012;
	sval[6] = 015;
	sval[7] = 011;
	sval[8] = 013;
	sval[9] = 0134;
	sval[10] = 129;
	sval[11] = 130;
	sval[12] = 0;
}

static int				display_special_char(char *str)
{
	int		sval[20];
	char	*schar;
	int		i;

	fill_sval(sval);
	schar = "abcefnrtv\\0x";
	i = 0;
	if (*str == '\\')
	{
		while (schar[i] && schar[i] != str[1])
			i++;
		if (i < ft_strlen(schar))
		{
			if (sval[i] >= -128 && sval[i] <= 127)
				ft_putchar((char)sval[i]);
			else if (sval[i] == 128)
				return (-1);
			else if (sval[i] == 129)
				return (display_octal(&str[2]) + 2);
			else if (sval[i] == 130)
				return (display_hexa(&str[2]) + 2);
			return (2);
		}
	}
	return (0);
}

static int				display_str(char *str, int opt)
{
	int i;
	int ret;

	i = 0;
	while (str[i])
	{
		ret = (opt & 0b1) ? display_special_char(&str[i]) : 0;
		if (ret > 0)
			i += ret;
		else if (ret == -1)
			return (1);
		else
		{
			ft_putchar(str[i]);
			i++;
		}
	}
	return (0);
}

static inline int		init_flags(char **av, int *flags, int save)
{
	int j;
	int i;
	int error;

	j = 0;
	while (av[++j] && av[j][0] == '-')
	{
		save = *flags;
		if (av[j][1] == '-' && av[j][2] == '\0')
			return (j + 1);
		i = 0;
		while (av[j][++i])
		{
			error = 0;
			(av[j][i] == 'e') ? (*flags |= 0b01) : (error += 1);
			(av[j][i] == 'E') ? (*flags &= 0b10) : (error += 1);
			(av[j][i] == 'n') ? (*flags |= 0b10) : (error += 1);
			*flags = (error == 3) ? save : *flags;
			if (error == 3)
				return (j);
		}
	}
	return (j);
}

void					ft_echo(char **av)
{
	int i;
	int flags;

	flags = 0;
	i = init_flags(av, &flags, 0);
	while (av[i])
	{
		if (display_str(av[i], flags))
			return ;
		i++;
		if (av[i])
			ft_putchar(' ');
	}
	if (!(flags & 0b10))
		write(1, "\n", 1);
}
