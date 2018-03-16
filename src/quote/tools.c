/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 16:48:02 by jlange            #+#    #+#             */
/*   Updated: 2018/01/23 17:45:38 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/quote.h"

int					ft_return(char c)
{
	if (c == '"')
		return (-1);
	else if (c == '\'')
		return (-2);
	else if (c == '`')
		return (-3);
	else
		return (0);
}

t_lineterm			*ft_ps2(t_lineterm *tmp)
{
	while (tmp)
	{
		if (tmp->c == '>')
		{
			tmp = tmp->next;
			break ;
		}
		tmp = tmp->next;
	}
	tmp = tmp->next;
	return (tmp);
}

char				*ft_ret_word_quote(char **wrd, int flag)
{
	static	char	*new;

	if (flag)
	{
		ft_strdel(&new);
		return (NULL);
	}
	if (!wrd || !(*wrd))
		return (new);
	*wrd = ft_free_join(*wrd, "\n", 'L');
	ft_join_all(*wrd, &new, 1);
	return (new);
}
