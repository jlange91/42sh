/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 19:23:41 by stvalett          #+#    #+#             */
/*   Updated: 2017/11/28 20:17:50 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/line_edition.h"
#include "../../inc/built_in.h"
#include "../../inc/globbing.h"
#include "../../inc/quote.h"

static void  ft_free_free(t_termc *sh)
{
	//free(sh->pwd);
	free(sh->line_shell);
	ft_free_dlist(&sh->line);
	ft_free_history(sh->history);
}

void			ft_cmd(t_shell *sh)
{
	if (!ft_strcmp(sh->av[0], "exit"))
	{
		ft_putstr("exit\n");
		exit(0);
	}
	else if (!ft_strcmp(sh->av[0], "echo"))
		ft_echo(sh->av);
	else if (!ft_strcmp(sh->av[0], "pwd"))
		ft_pwd(sh);
	else if (!ft_strcmp(sh->av[0], "setenv"))
		ft_prepare_setenv(sh);
	else if (!ft_strcmp(sh->av[0], "unsetenv"))
		ft_prepare_unsetenv(sh);
	else if (!ft_strcmp(sh->av[0], "env"))
		ft_env(sh);
	else if (!ft_strcmp(sh->av[0], "cd"))
		ft_cd(sh);
	else if (sh->av[0])
		ft_exec(sh->av, sh->env);
	//printf("{%d}\n", ft_singleton(0,0));
}

static void	ft_update_pwd_to_tsh(t_shell sh, t_termc *tsh)
{
	if (sh.pwd)
	{
		if (tsh->pwd)
			free(tsh->pwd);
		tsh->pwd = ft_strdup(sh.pwd);
	}
}

static int	ft_start_preparsing(t_termc *tsh, t_shell sh)
{
	while (42)
	{
		ft_singleton(0, 1);	
		signal(SIGINT, ft_handle_signal);
		signal(SIGWINCH, ft_handle_signal);		// NO FINISH
		ft_fill_history(tsh);
		ft_update_pwd_to_tsh(sh, tsh);
		ft_fill_line(tsh, sh.env);				// replace glob is in fct ft_line_input
		sh.line = ft_strdup(tsh->line_shell);
		ft_free_free(tsh);		
		ft_replace(&sh);
		ft_add_file_history(tsh);
		write(1, "\n", 1);
		ft_redirection(&sh);
		sh.av = ft_fill_av(sh.line);
		sh.ac = tab_2d_len(sh.av);
		if (sh.av[0] && sh.av[0][0])
			ft_cmd(&sh);
		ft_remove_redirection(&sh);
		ft_end_term(tsh);
		free_tab_2d(sh.av);
		free(sh.line);
	}
	return (ft_singleton(0, 0));
}

int	ft_line_edition(t_termc *shell, t_shell sh)
{
	if (ft_start_preparsing(shell, sh) == 0)
	{
		if (shell->from_hist->ecrase_hist == 1)
			ft_add_file_history_no_flag(shell);
		else
			ft_add_file_history(shell);
		return (0);
	}
	return (1);
}
