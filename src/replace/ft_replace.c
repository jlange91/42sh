/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 18:22:31 by jlange            #+#    #+#             */
/*   Updated: 2017/11/03 18:23:13 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"

static int		backslash_word(char *line)
{
	if (line[0] != '\\')
		return (0);
	if (line[1] == '\n')
		return (2);
	else
		return (1);
}

int				ft_skip_quote(char *str)
{
	int i;

	i = 1;
	if (str[0] == '\'')
	{
		while (str[i] != '\'')
			i++;
		return (i);
	}
	else
		return (0);
}

void			ft_replace(t_shell *sh)
{
	int i;

	i = 0;
	while (sh->line[i])
	{
		i += ft_skip_quote(&sh->line[i]);
		if (sh->line[i] == '$' && ft_isalnum(sh->line[i + 1]))
		{
			ft_replace_dollar(sh, i);
			i--;
		}
		if (sh->line[i] == '~')
		{
			ft_replace_tilde(sh, i);
			i--;
		}
		if (backslash_word(&sh->line[i]) > 0)
			i++;
		i++;
	}
}
