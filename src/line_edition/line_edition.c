/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 19:23:41 by stvalett          #+#    #+#             */
/*   Updated: 2017/12/20 18:04:28 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/line_edition.h"
#include "../../inc/built_in.h"
#include "../../inc/globbing.h"
#include "../../inc/quote.h"

void			ft_cmd(t_cmd *cmd)
{
	t_termc *tsh;

	tsh = ft_ret_tsh(NULL);
	if (!ft_strcmp(cmd->av[0], "exit"))
	{
		ft_add_file_history(tsh);
		ft_putstr("exit\n");
		exit(0);
	}
	else if (!ft_strcmp(cmd->av[0], "echo"))
		ft_echo(cmd->av);
	else if (!ft_strcmp(cmd->av[0], "pwd"))
		ft_pwd(cmd);
	else if (!ft_strcmp(cmd->av[0], "setenv"))
		ft_prepare_setenv(cmd);
	else if (!ft_strcmp(cmd->av[0], "unsetenv") ||
			!ft_strcmp(cmd->av[0], "unset"))
		ft_prepare_unsetenv(cmd);
	else if (!ft_strcmp(cmd->av[0], "env"))
		ft_env(cmd);
	else if (!ft_strcmp(cmd->av[0], "cd"))
		ft_cd(cmd);
	else if(!ft_strcmp(cmd->av[0], "help"))
		ft_help(cmd);
	else if(!ft_strcmp(cmd->av[0], "export"))
		prepare_export(cmd);
	else if (!ft_strcmp(cmd->av[0], "history")) //HISTORY OPTION FINIS, NO EXPANSION
		history(cmd);
	else if (cmd->av[0])
		ft_exec(cmd->av, cmd->env);
	//printf("{%d}\n", ft_singleton(0,0));
}

int	ft_line_edition(t_termc *tsh, t_cmd *cmd)
{


		ft_singleton(0, 1);
		ft_redirection(cmd);
		cmd->av = ft_fill_av(cmd->line);
		cmd->ac = tab_2d_len(cmd->av);
		if (cmd->av[0] && cmd->av[0][0])
			ft_cmd(cmd);
		ft_remove_redirection(cmd);
		ft_end_term(tsh);
		free_tab_2d(cmd->av);


	return (ft_singleton(0, 0));
}
