/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 11:25:56 by vmartins          #+#    #+#             */
/*   Updated: 2018/01/25 12:09:22 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sh21.h"
#include "../inc/line_edition.h"
#include "../inc/built_in.h"
#include "../inc/globbing.h"
#include "../inc/quote.h"

void	free_shell(t_termc *tsh)
{
	ft_reinit_hash();
	free_tab_2d(ft_var_env(NULL));
	free(ft_var_pwd(NULL));
	ft_free_all(tsh);
}

void	ft_free_free(t_termc *tsh)
{
	free(tsh->line_shell);
	ft_free_t_dlst(&tsh->line);
	ft_free_history(tsh->histmp);
}

void	ft_free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		free_tab_2d(cmd->av);
		free(cmd->line);
		if (cmd->hrdc)
			free(cmd->hrdc);
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}
