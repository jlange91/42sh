/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 16:28:44 by jlange            #+#    #+#             */
/*   Updated: 2018/02/13 16:17:53 by jlange           ###   ########.fr       */
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

static inline int		exec_red(t_redir *red, t_cmd *cmd)
{
	if (red->type == 8)
		ft_redirr_type8(red);
	else if (red->type == 1 || red->type == 4 ||
			red->type == 3 || red->type == 7)
	{
		if (ft_redirr_type1(red))
			return (1);
	}
	else if (red->type == 2 || red->type == 5)
	{
		if (ft_redirr_type2(red))
			return (1);
	}
	else if (red->type == 6)
	{
		if (cmd->hrdc)
		{
			write(red->out, cmd->hrdc, ft_strlen(cmd->hrdc));
			close(red->out);
			red->out = open(ft_var_hrdcpwd(NULL), O_RDWR | O_CREAT, 0644);
			ft_redirr_type2(red);
		}
	}
	return (0);
}

static inline void		init_backup(int *i)
{
	*i = 0;
	ft_backup_stdin(1);
	ft_backup_stdout(1);
	ft_backup_stderr(1);
}

static inline void		change_cmd(t_cmd *cmd)
{
	free_tab_2d(cmd->av);
	cmd->av = ft_fill_av(cmd->line);
	cmd->ac = tab_2d_len(cmd->av);
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
			red = type_redir(&cmd->line[i], i, 0, -1);
			if ((red->out == -1 && red->type != 8) || exec_red(red, cmd))
			{
				free(red);
				return (-1);
			}
			free(red);
		}
		if (backslash_word(&cmd->line[i]) > 0)
			i++;
		i++;
	}
	change_cmd(cmd);
	return (0);
}
