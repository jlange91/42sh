/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 16:46:46 by jlange            #+#    #+#             */
/*   Updated: 2018/03/06 16:32:12 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/quote.h"
#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"

void	ft_fill_line(t_termc *tsh)
{
	char	*tmp;
	char	*line;

	line = NULL;
	if ((line = ft_readline(tsh)) == NULL)
		exit(1);
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
