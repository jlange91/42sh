/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_tilde.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 18:22:40 by jlange            #+#    #+#             */
/*   Updated: 2017/12/20 17:18:08 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"

static char		*get_value(t_cmd *cmd)
{
    char *value;

	value = ft_getenv("HOME", cmd->env);
	if (value)
	{
		while (*value != '=')
			++value;
		++value;
	}
	return (value);
}

void			ft_replace_tilde(t_cmd *cmd, int i)
{
	char	*str1;
	char	*value;
	char	*str2;

	str1 = ft_strndup(cmd->line, i);
	value = get_value(cmd);
    str2 = ft_strdup(&cmd->line[i + 1]);
	free(cmd->line);
    cmd->line = ft_replace_line(str1, value, str2);
	free(str1);
    free(str2);
}
