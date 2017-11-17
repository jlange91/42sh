/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_tilde.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 18:22:40 by jlange            #+#    #+#             */
/*   Updated: 2017/11/03 18:24:08 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"

static char		*get_value(t_shell *sh)
{
    char *value;

	value = ft_getenv("HOME", sh->env);
	if (value)
	{
		while (*value != '=')
			++value;
		++value;
	}
	return (value);
}

void			ft_replace_tilde(t_shell *sh, int i)
{
	char	*str1;
	char	*value;
	char	*str2;

	str1 = ft_strndup(sh->line, i);
	value = get_value(sh);
    str2 = ft_strdup(&sh->line[i + 1]);
	free(sh->line);
    sh->line = ft_replace_line(str1, value, str2);
	free(str1);
    free(str2);
}
