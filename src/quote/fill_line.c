/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 16:46:46 by jlange            #+#    #+#             */
/*   Updated: 2018/01/23 17:43:17 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/quote.h"
#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"

void	ft_fill_line(t_termc *tsh)
{
	char	*tmp;
	char	*line;

	line = ft_readline(tsh);
	if (tsh->quotes)
	{
		tmp = NULL;
		tsh->quotes = 0;
		free(line);
		tsh->line_shell = ft_strdup(ft_ret_word_quote(&tmp, 0));
		tsh->line_shell[ft_strlen(tsh->line_shell) - 1] = '\0';
		ft_ret_word_quote(&tmp, 1);
	}
	else
	{
		tsh->line_shell = ft_strdup(line);
		free(line);
	}
	ft_end_term(tsh);
}
