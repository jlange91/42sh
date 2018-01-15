/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirrection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 18:22:31 by jlange            #+#    #+#             */
/*   Updated: 2017/12/12 14:54:08 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"
#include "../../inc/quote.h"

static int		backslash_word(char *line)
{
	if (line[0] != '\\')
		return (0);
	if (line[1] == '\n')
		return (2);
	else
		return (1);
}

int			ft_redirection(t_cmd *cmd)
{
	int i;
	t_redir *red;

	i = 0;
	ft_backup_stdin(1);
	ft_backup_stdout(1);
	ft_backup_stderr(1);
	while (cmd->line[i])
	{
        i += ft_skip_quote(&cmd->line[i]);
		i += ft_skip_dquote(&cmd->line[i]);
		if ((cmd->line[i] == '>' || cmd->line[i] == '<') && !(i > 0 && cmd->line[i - 1] == '\\'))
		{
			red = type_redir(&cmd->line[i], i);
			if (red->out == -1)
			{
				free_tab_2d(cmd->av);
				cmd->av = ft_fill_av(cmd->line);
				cmd->ac = tab_2d_len(cmd->av);
				return (-1);
			}
			if (red->type == 8)
				ft_redirr_type8(red);
			else if (red->type == 1 || red->type == 4 || red->type == 3 || red->type == 7)
				ft_redirr_type1(red);
			else if (red->type == 2 || red->type == 5)
				ft_redirr_type2(red);
			if (red->close)
				close(red->out);
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

// void test_fd()
// {
// 	for(int i = 3; i < 10000; i++)
// 	{
// 		if (close(i)) {
// 		} else {
// 			    dprintf(2, "%d, ", i);
// 				 }
// 	}
// 	dprintf(2, "etait ouvert\n");
// }