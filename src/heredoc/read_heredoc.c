/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 15:04:12 by stvalett          #+#    #+#             */
/*   Updated: 2018/01/23 16:00:20 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"
#include "../../inc/sh21.h"

static	int		ft_key_and_char1(t_termc *tsh, long c, char *word)
{
	if ((char)c == '\n')
	{
		if (ft_line_hdoc(tsh, word))
			return (0);
		return (1);
	}
	if ((char)c == EOT)
		ft_ctr_d(tsh);
	if ((ft_action_key(tsh->line, tsh, c) == 0 && ft_isprint((char)c)))
	{
		if (tsh->line->lnk_before)
			ft_insert_dlnk(tsh->line->end, tsh, c, 1);
		else
			push_backdlst(tsh->line, c, 1);
		if (ft_isprint((char)c) && c != BACKSPACE && c
				!= LEFT && c != RIGHT && c != UP && c != DOWN)
			ft_find_history(tsh);
	}
	else
		tsh->line->lnk_before = 1;
	if (tsh->line->last)
		tsh->line->lnk_before = 0;
	return (1);
}

static	char	*ft_readline_hdoc(char *word, t_termc *tsh)
{
	char		k;
	long		c;
	static int	stop;

	if (isatty(0))
	{
		tsh->hdoc = 1;
		ft_fill_history(tsh);
		ft_display_prompt_hdoc(tsh);
		while (read(0, &k, sizeof(k)))
		{
			if (ft_signal_here(tsh))
				return ("\0");
			if (ft_what_key(&c, &stop, k))
				continue ;
			if (!ft_key_and_char1(tsh, c, word))
				break ;
			ft_display(tsh);
		}
		ft_free_dlist(&tsh->line);
		write(1, "\n", 1);
		return (ft_ret_word_hdoc(NULL, 0));
	}
	return (NULL);
}

static void		fill_cmd_hrdc(t_cmd *cmd, t_termc *tsh, int i)
{
	char		*word;

	word = ft_ret_word(&cmd->line[i]);
	if (cmd->hrdc)
		free(cmd->hrdc);
	cmd->hrdc = ft_strdup(ft_readline_hdoc(word, tsh));
	if (word)
		free(word);
	ft_ret_word_hdoc(NULL, 1);
}

int				ft_hdoc(t_cmd *cmd)
{
	int			i;
	t_termc		*tsh;

	i = 0;
	tsh = ft_ret_tsh(NULL);
	ft_init_terminal_mode(tsh);
	while (cmd->line[i])
	{
		i += ft_skip_quote(&cmd->line[i]);
		i += ft_skip_dquote(&cmd->line[i]);
		if (cmd->line[i] == '<' && cmd->line[i + 1] == '<')
		{
			i += 2;
			fill_cmd_hrdc(cmd, tsh, i);
		}
		if (ft_backslash_word(&cmd->line[i]) > 0)
			i++;
		i++;
	}
	ft_end_term(tsh);
	return (0);
}
