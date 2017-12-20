/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 18:22:31 by jlange            #+#    #+#             */
/*   Updated: 2017/12/20 17:17:44 by jlange           ###   ########.fr       */
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

void			ft_replace(t_cmd *cmd)
{
	int i;

	i = 0;
	while (cmd->line[i])
	{
		i += ft_skip_quote(&cmd->line[i]);
		if (cmd->line[i] == '$' && ft_isalnum(cmd->line[i + 1]))
		{
			ft_replace_dollar(cmd, i);
			i--;
		}
		if (cmd->line[i] == '~')
		{
			ft_replace_tilde(cmd, i);
			i--;
		}
		if (backslash_word(&cmd->line[i]) > 0)
			i++;
		i++;
	}
}
