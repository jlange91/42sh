/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_dollar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 18:22:40 by jlange            #+#    #+#             */
/*   Updated: 2017/12/20 17:17:58 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"

static char		*get_value(t_cmd *cmd, int *i)
{
	char	*tmp;
	char	*value;
	int		j;

	j = 0;
	*i += 1;
	while (cmd->line[*i + j] && ft_isalnum(cmd->line[*i + j]))
		++j;
	tmp = ft_strndup(&cmd->line[*i], j);
	value = ft_getenv(tmp, cmd->env);
	if (value)
	{
		while (*value != '=')
			++value;
		++value;
	}
	*i += j;
	free(tmp);
	return (value) ? ft_strdup(value) : value;
}

void			ft_replace_dollar(t_cmd *cmd, int i)
{
	char	*str1;
	char	*value;
	char	*str2;

	str1 = ft_strndup(cmd->line, i);
	value = get_value(cmd, &i);
	if (value)
		value = ft_add_escape(value);
	str2 = ft_strdup(&cmd->line[i]);
	free(cmd->line);
	cmd->line = ft_replace_line(str1, value, str2);
	free(str1);
	free(str2);
	free(value);
}
