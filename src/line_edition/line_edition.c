/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 19:23:41 by stvalett          #+#    #+#             */
/*   Updated: 2017/12/20 17:15:46 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/line_edition.h"
#include "../../inc/built_in.h"
#include "../../inc/globbing.h"
#include "../../inc/quote.h"

static void  ft_free_free(t_termc *sh)
{
	free(sh->line_shell);
	ft_free_dlist(&sh->line);
	ft_free_history(sh->history);
}

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

static void	ft_update_pwd_to_tsh(t_cmd cmd, t_termc *tsh)
{
	if (cmd.pwd)
	{
		if (tsh->pwd)
			free(tsh->pwd);
		tsh->pwd = ft_strdup(cmd.pwd);
	}
}

int	ft_line_edition(t_termc *tsh, t_cmd cmd)
{
	ft_ret_cmd(&cmd);
	ft_ret_tsh(&tsh);
	while (42)
	{
		signal(SIGINT, ft_handle_signal);
		ft_singleton(0, 1);
		ft_update_pwd_to_tsh(cmd, tsh);
		ft_fill_history(tsh);
		ft_fill_line(tsh);				// replace glob is in fct ft_line_input
		cmd.line = ft_strdup(tsh->line_shell);
		ft_free_free(tsh);
		ft_replace(&cmd);
		write(1, "\n", 1);
		ft_redirection(&cmd);
		cmd.av = ft_fill_av(cmd.line);
		cmd.ac = tab_2d_len(cmd.av);
		if (cmd.av[0] && cmd.av[0][0])
			ft_cmd(&cmd);
		ft_remove_redirection(&cmd);
		ft_end_term(tsh);
		free_tab_2d(cmd.av);
		free(cmd.line);
	}
	return (ft_singleton(0, 0));
}
