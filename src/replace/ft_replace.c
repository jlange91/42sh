/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 18:22:31 by jlange            #+#    #+#             */
/*   Updated: 2017/12/20 18:10:46 by jlange           ###   ########.fr       */
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
