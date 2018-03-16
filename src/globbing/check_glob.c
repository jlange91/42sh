/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_glob.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 15:10:08 by vmartins          #+#    #+#             */
/*   Updated: 2017/12/19 15:10:10 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/globbing.h"

int		ft_only_star(char *word)
{
	int	i;

	i = 0;
	while (word[i] && word[i] == '*')
		i++;
	if (word[i] == '\0')
		return (1);
	return (0);
}

int		ft_glob_here(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if ((str[i] == '*' || str[i] == '?'
					|| str[i] == '[' || str[i] == '{')
				&& !(i > 0 && str[i - 1] == '\\'))
			return (1);
	}
	return (0);
}

int		ft_syntax_braces(char *word)
{
	int i;
	int count;
	int count2;
	int comma;

	i = -1;
	count = 0;
	count2 = 0;
	comma = 0;
	while (word[++i])
	{
		if (word[i] == '{' && !(i > 0 && word[i - 1] == '\\'))
			count++;
		if (word[i] == '}' && !(i > 0 && word[i - 1] == '\\'))
			count2++;
		if (word[i] == ',' && !(i > 0 && word[i - 1] == '\\'))
			comma = 1;
	}
	if (!count && !count2 && !comma)
		return (0);
	if (count == count2 && comma == 1
			&& count == 1 && count2 == 1)
		return (1);
	return (0);
}

int		ft_syntax_bracket(char *word)
{
	int i;
	int count;
	int count2;

	i = -1;
	count = 0;
	count2 = 0;
	while (word[++i])
	{
		if (word[i] == '[' && !(i > 0 && word[i - 1] == '\\'))
			count++;
		if (((word[i] == '{' && count != 0) || (word[i] == '}' && count2 == 0))
		&& !(i > 0 && word[i - 1] == '\\'))
			return (0);
		if (word[i] == ']' && !(i > 0 && word[i - 1] == '\\'))
			count2++;
	}
	if (count == count2)
		return (1);
	return (0);
}
