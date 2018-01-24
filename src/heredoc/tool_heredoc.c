/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 15:04:43 by stvalett          #+#    #+#             */
/*   Updated: 2018/01/22 16:15:13 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"
#include "../../inc/sh21.h"

void			ft_display_prompt_hdoc(t_termc *tsh)
{
	int			i;
	char		*prompt;

	ft_free_dlist(&tsh->line);
	tsh->line->lnk_before = 0;
	prompt = "heredoc> ";
	i = -1;
	while (prompt[++i])
		push_backdlst(tsh->line, prompt[i], 0);
	ft_display(tsh);
}

char			*ft_ret_word_hdoc(char **wrd, int flag)
{
	static char	*new;

	if (flag)
	{
		if (new != NULL)
			ft_strdel(&new);
		return (NULL);
	}
	if (!wrd || !(*wrd))
		return (new);
	if (*(*wrd + ft_strlen(*wrd) - 1) == '\\' &&
			*(*wrd + ft_strlen(*wrd) - 2) != '\\')
		ft_join_all(*wrd, &new, 1);
	else
	{
		*wrd = ft_free_join(*wrd, "\n", 'L');
		ft_join_all(*wrd, &new, 1);
	}
	return (new);
}

int				ft_line_hdoc(t_termc *t, char *word)
{
	char		*tmp;
	int			i;

	tmp = ft_to_str(t, 1);
	if (ft_strcmp(word, tmp) == 0)
	{
		t->hdoc = 0;
		free(tmp);
		return (1);
	}
	else
	{
		ft_ret_word_hdoc(&tmp, 0);
		i = 0;
		while (i < (int)t->console->total_line)
		{
			tputs(t->term->dostr, 1, ft_inputstr);
			i++;
		}
		ft_display_prompt_hdoc(t);
		ft_find_history(t);
	}
	return (0);
}

int				ft_signal_here(t_termc *tsh)
{
	if (tsh->sigint)
	{
		tputs(tsh->term->upstr, 1, ft_inputstr);
		tputs(tsh->term->upstr, 1, ft_inputstr);
		ft_free_dlist(&tsh->line);
		ft_ret_word_hdoc(NULL, 1);
		return (1);
	}
	return (0);
}
