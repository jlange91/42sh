/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 19:23:41 by stvalett          #+#    #+#             */
/*   Updated: 2017/10/17 12:02:54 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/line_edition.h"
#include "../../inc/token.h"
#include "../../inc/env_term.h"
#include "../../inc/tree.h"
#include "../../inc/exec.h"
#include "../../inc/globbing.h"

static void  ft_free_free(t_shell *shell, t_lexer *lexer, t_env *env_c, t_tree *root, int flag)
{
	if (flag)
	{
		ft_free_dlist(&shell->line);
		ft_free_dlist_token(&(lexer)->token);
		free(env_c->line_str);
		ft_free_ast(root);
	}
	else
	{
		free(env_c->line_str);
		ft_free_dlist(&shell->line);
		ft_free_history(shell->history);
		ft_free_ast(root);
	}
}


static int	ft_start_preparsing(t_shell *shell, t_env *env_c, t_lexer *lexer)
{
	t_tree  *tree;
	t_glob  *glob;

	while (42)
	{
		tree = NULL;
		glob = NULL;
		signal(SIGINT, ft_handle_signal);
		signal(SIGWINCH, ft_handle_signal);
		ft_fill_history(shell);
		if ((env_c->line_str = ft_line_input(shell, env_c)) == NULL && shell->keyflag->cl != 1)
			return (0);
		if (shell->keyflag->cl != 1)
		{

			// lexer->token = ft_parse_token(env_c->line_str, lexer);
			ft_parse_glob(env_c->line_str, &glob, env_c);

			char **av;

			av = ft_fill_av(env_c->line_str);
			
			// if (lexer->token->type != -1)
			// {
				// ft_parse(lexer, &tree);
				// if (!ft_execute(tree, env_c, lexer))
				// {
				// 	ft_free_free(shell, lexer, env_c, tree, 0);
				// 	return (0);
				// }
			// }
			ft_end_term(shell);
			if (shell->from_hist->ecrase_hist == 1)
				ft_add_file_history_no_flag(shell);
			else
				ft_add_file_history(shell);
		}
		ft_free_free(shell, lexer, env_c, tree, 1);
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
