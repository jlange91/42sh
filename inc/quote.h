/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 17:45:16 by vmartins          #+#    #+#             */
/*   Updated: 2018/01/24 17:02:42 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTE_H
# define QUOTE_H

# include "sh21.h"

# define Q_LEFT 'D'
# define Q_RIGHT 'C'

/*
**CHECK.C
*/

int			ft_check_quote(char *line);

/*
**MAIN_QUOTE.C
*/

char		**ft_fill_av(char *line);

/*
**COUNT1.C
*/

int			ft_count_av1(char *line);

/*
**COUNT2.C
*/

int			ft_count_av2(char *line, char **av);

/*
**FILL.C
*/

void		ft_fill(char *line, char **av);

/*
**FILL_LINE.C
*/

void		ft_fill_line(t_termc *shell);
int			ft_char_escape(char c);

/*
**TOOLS
*/

int			ft_return(char c);
t_lineterm	*ft_ps2(t_lineterm *tmp);
char		*ft_ret_word_quote(char **wrd, int flag);

/*
**READ_QUOTE.C
*/

int			ft_line_quotes(t_termc *sh);

#endif
