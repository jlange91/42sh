/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 18:22:31 by jlange            #+#    #+#             */
/*   Updated: 2017/11/17 11:10:38 by jlange           ###   ########.fr       */
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

int				ft_skip_dquote(char *str)
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

int             type_redir(char *str, int index)
{
    int ret;

    ret = 0;
    if (index > 0 && str[-1] == '\\')
        return (0);
    ret =  (str[0] == '>') ? 1 : ret;
    ret =  (str[0] == '>' && str[1] == '>') ? 2 : ret;
    ret =  (str[0] == '>' && str[1] == '&') ? 3 : ret;
    ret =  (str[0] == '<') ? 4 : ret;
    return (ret);
}

void			ft_redirection(t_shell *sh)
{
	int i;

	i = 0;
	while (sh->line[i])
	{
        i += ft_skip_quote(&sh->line[i]);
        i += ft_skip_dquote(&sh->line[i]);
        if (type_redir(&sh->line[i], i) > 0)
            
		if (backslash_word(&sh->line[i]) > 0)
			i++;
		i++;
	}
}