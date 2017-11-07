/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 19:23:41 by stvalett          #+#    #+#             */
/*   Updated: 2017/11/02 18:35:20 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/line_edition.h"
#include "../../inc/token.h"
#include "../../inc/env_term.h"
#include "../../inc/tree.h"
#include "../../inc/exec.h"
#include "../../inc/globbing.h"
#include "../../inc/quote.h"

static void  ft_free_free(t_shell *shell, t_env *env_c)
{
	ft_free_dlist(&shell->line);
	free(env_c->line_str);
	ft_free_history(shell->history);
}

static int	ft_start_preparsing(t_shell *shell, t_env *env_c, t_lexer *lexer)
{
	(void)lexer;
	while (42)
	{
		signal(SIGINT, ft_handle_signal);
		signal(SIGWINCH, ft_handle_signal);  //toudoux because is not fucking finish0
		ft_fill_history(shell);
		ft_fill_line(shell, env_c);
		// a inserer ft_replace()
		// a inserer fill_av()
		// a inserer ft_exec()
		if (ft_strcmp(env_c->line_str, "exit") == 0)
		{
			ft_free_free(shell, env_c);
			return (0);
		}
		ft_end_term(shell);
		ft_free_free(shell, env_c);
	}
	return (1);
}

int	ft_line_edition(t_env *env_c, t_shell *shell, t_lexer *lexer)
{
	if (ft_start_preparsing(shell, env_c, lexer) == 0)
	{
		if (shell->from_hist->ecrase_hist == 1)
			ft_add_file_history_no_flag(shell);
		else
			ft_add_file_history(shell);
		return (0);
	}
	return (1);
}
