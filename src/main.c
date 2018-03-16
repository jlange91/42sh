/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 11:25:18 by vmartins          #+#    #+#             */
/*   Updated: 2018/01/31 15:06:00 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sh21.h"
#include "../inc/line_edition.h"
#include "../inc/built_in.h"
#include "../inc/globbing.h"
#include "../inc/quote.h"

static void	ft_exec_all_cmd2(t_cmd *cmd)
{
	int	val;
	int	ret;

	ret = 0;
	val = 1;
	while (cmd)
	{
		if (val == 1 && cmd->l_op != 4)
			ret = ft_builtin_and_exec(cmd);
		cmd = cmd->next;
		if (cmd)
		{
			if (cmd->l_op == 2)
				val = (ret != 0) ? 0 : 1;
			else if (cmd->l_op == 3)
				val = (ret == 0) ? 0 : 1;
			else
				val = 1;
		}
	}
}

static void	ft_exec_all_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_termc	*tsh;

	tmp = cmd;
	tsh = ft_ret_tsh(NULL);
	while (tmp)
	{
		ft_hdoc(tmp);
		tmp = tmp->next;
	}
	if (tsh->sigint)
		return ;
	ft_exec_all_cmd2(cmd);
}

static	int	ft_fill_line_and_replace(t_termc *tsh, t_shell *sh, t_cmd *cmd)
{
	ft_fill_history(tsh);
	ft_fill_line(tsh);
	if (tsh->keyflag->cl)
	{
		ft_free_free(tsh);
		return (0);
	}
	sh->line = ft_strdup(tsh->line_shell);
	ft_free_free(tsh);
	ft_result_replace(sh);
	if (sh->line == NULL || tsh->repl)
		return (0);
	if (tsh->save_line && ft_strlen(tsh->save_line) > 1)
		ft_add_tmp_history(tsh, tsh->save_line);
	ft_strdel(&tsh->save_line);
	if (ft_check_cmd(sh) || ft_check_redir(sh))
	{
		free(sh->line);
		return (0);
	}
	cmd = ft_fill_cmd(sh->line, 0, 0);
	free(sh->line);
	ft_exec_all_cmd(cmd);
	ft_free_cmd(cmd);
	return (1);
}

int			main(int ac, char **av, char **env)
{
	t_termc	*tsh;
	t_cmd	*cmd;
	t_shell	sh;

	(void)ac;
	(void)av;
	tsh = NULL;
	cmd = NULL;
	if (!isatty(0))
		return (1);
	ft_fill_env(env);
	tsh = init_termc(ft_var_env(NULL));
	ft_memset(&sh, 0, sizeof(sh));
	ft_ret_sh(&sh);
	ft_ret_tsh(&tsh);
	ft_init_signal();
	ft_var_hrdcpwd(ft_strjoin(ft_var_pwd(NULL), "/.heredocs_42sh"));
	while (42)
	{
		if (!ft_fill_line_and_replace(tsh, &sh, cmd))
			continue ;
	}
	free(ft_var_hrdcpwd(NULL));
	free_shell(tsh);
	return (0);
}
