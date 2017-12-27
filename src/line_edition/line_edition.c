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


// void					ft_pipe(t_cmd *cmd, char **av, char **env)
// {
// 	int		pipefd[2];

// 	pipe(pipefd);



// 	// int		status;
// 	// pid_t	father;
// 	// int		ret;

// 	// father = fork();
// 	// if (father > 0)
// 	// {
// 	// 	signal(SIGINT, SIG_IGN);
// 	// 	wait(&status);
// 	// 	ft_singleton(status, 1);
// 	// 	signal(SIGINT, ft_handle_signal);
// 	// }
// 	// if (father == 0)
// 	// {
// 	// 	ret = (av[0][0] == '/' || (av[0][0] == '.' && (av[0][1] == '.' ||
// 	// 	av[0][1] == '/'))) ? exec_av(av, env) : exec_path(av, env);
// 	// 	if (ret != 0)
// 	// 	{
// 	// 		if (ret == 2)
// 	// 		{
// 	// 			ft_putstr_fd("shell: command not found: ", 2);
// 	// 			ft_putendl_fd(av[0], 2);
// 	// 		}
// 	// 		else
// 	// 			ft_perror("shell", errno, av[0]);
// 	// 		exit(1);
// 	// 	}
// 	// }	
// }

void			ft_cmd(t_cmd *cmd)
{
	t_termc *tsh;

	tsh = ft_ret_tsh(NULL);
	// if (cmd->r_op == 4)
	// {
	// 	ft_pipe(cmd, av, env);
	// 	return ;
	// }
	if (!ft_strcmp(cmd->av[0], "exit"))
	{
		ft_add_file_history(tsh);
		ft_putstr("exit\n");
		exit(0);
	}
	else if (!ft_strcmp(cmd->av[0], "echo"))
		ft_echo(cmd->av);
	else if (!ft_strcmp(cmd->av[0], "pwd"))
		ft_pwd(cmd->av);
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
		ft_help();
	else if(!ft_strcmp(cmd->av[0], "export"))
		prepare_export(cmd);
	else if (!ft_strcmp(cmd->av[0], "history")) //HISTORY OPTION FINIS, NO EXPANSION
		history(cmd);
	else if (cmd->av[0])
		ft_exec(cmd->av, ft_var_env(NULL));
	//printf("{%d}\n", ft_singleton(0,0));
}

int	ft_line_edition(t_cmd *cmd)
{
	ft_singleton(0, 1);
	ft_redirection(cmd);
	if (cmd->av[0] && cmd->av[0][0])
		ft_cmd(cmd);
	ft_remove_redirection(cmd);
//	ft_end_term(tsh); déplacé dans le main
	return (ft_singleton(0, 0));
}
