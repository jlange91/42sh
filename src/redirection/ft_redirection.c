/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 16:28:44 by jlange            #+#    #+#             */
/*   Updated: 2018/01/19 16:34:33 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"
#include "../../inc/quote.h"

static inline int		backslash_word(char *line)
{
	if (line[0] != '\\')
		return (0);
	if (line[1] == '\n')
		return (2);
	else
		return (1);
}

static inline void		exec_red(t_redir *red, t_cmd *cmd)
{
	if (red->type == 8)
		ft_redirr_type8(red);
	else if (red->type == 1 || red->type == 4 ||
			red->type == 3 || red->type == 7)
		ft_redirr_type1(red);
	else if (red->type == 2 || red->type == 5)
		ft_redirr_type2(red);
	else if (red->type == 6)
	{
		if (cmd->hrdc)
		{
			write(red->out, cmd->hrdc, ft_strlen(cmd->hrdc));
			lseek(red->out, 0, SEEK_SET);
			ft_redirr_type2(red);
		}
	}
	if (red->close)
		close(red->out);
}

static inline void		init_backup(int *i)
{
	*i = 0;
	ft_backup_stdin(1);
	ft_backup_stdout(1);
	ft_backup_stderr(1);
}

int						ft_redirection(t_cmd *cmd)
{
	int		i;
	t_redir	*red;

	init_backup(&i);
	while (cmd->line[i])
	{
		i += ft_skip_quote(&cmd->line[i]);
		i += ft_skip_dquote(&cmd->line[i]);
		if ((cmd->line[i] == '>' || cmd->line[i] == '<') &&
				!(i > 0 && cmd->line[i - 1] == '\\'))
		{
			red = type_redir(&cmd->line[i], i, 0, 0);
			if (red->out == -1)
				return (-1);
			exec_red(red, cmd);
			free(red);
		}
		if (backslash_word(&cmd->line[i]) > 0)
			i++;
		i++;
	}
	free_tab_2d(cmd->av);
	cmd->av = ft_fill_av(cmd->line);
	cmd->ac = tab_2d_len(cmd->av);
	return (0);
}
