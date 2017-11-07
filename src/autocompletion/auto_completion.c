/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 10:23:22 by stvalett          #+#    #+#             */
/*   Updated: 2017/11/02 17:49:13 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/autocompletion.h"
#include "../../inc/globbing.h"

void    ft_ajuste_and_fill_line(t_shell *shell, char *data, char *before, t_env *env)
{
	int         i;

	free(shell->autocompl->str);
	ft_free_dlist(&shell->line); 
	ft_init_console(shell, shell->line, env);
	if (!shell->history->active)
	{
		tputs(shell->term->upstr, 1, ft_inputstr);
		tputs(shell->term->upstr, 1, ft_inputstr);
	}
	shell->autocompl->str = ft_strdup(data);
	i = -1;
	while (before[++i])
		ft_fill_back_dlst(shell->line, before[i], i + 2);
	i = -1;
	while (data[++i])
		ft_fill_back_dlst(shell->line, data[i], i + 2);
	ft_check_is_dir(shell);
}

int		ft_autocompl_complex(t_shell *shell, char *data, char *before, char *after, t_env *env)
{
	if (ft_count(shell->autocompl) == 1)
	{
		if (ft_strncmp(after, data, ft_strlen(after)) == 0)
		{
			ft_ajuste_and_fill_line(shell, data, before, env);
			return (1);
		}
	}
	else
	{
		if (ft_strcmp(after, data) == 0)
		{
			ft_ajuste_and_fill_line(shell, data, before, env);
			return (1);
		}
	}
	return (0);
}

int		ft_autocompl_simple(t_shell *shell, char *data, t_env *env)
{
	int         i;
	struct stat info_data;

	if (ft_count(shell->autocompl) == 1)
	{
		if (ft_strncmp(shell->autocompl->str, data, ft_strlen(shell->autocompl->str)) == 0)
		{
			free(shell->autocompl->str);
			ft_free_dlist(&shell->line); 
			ft_init_console(shell, shell->line, env);
			if (!shell->history->active)
			{
				tputs(shell->term->upstr, 1, ft_inputstr);
				tputs(shell->term->upstr, 1, ft_inputstr);
			}
			shell->autocompl->str = ft_strdup(data);
			i = -1;
			stat(data, &info_data);
			while (shell->autocompl->str[++i])
				ft_fill_back_dlst(shell->line, shell->autocompl->str[i], i + 2);
			if (S_ISDIR(info_data.st_mode))
				ft_fill_back_dlst(shell->line, '/', i + 2);
			return (1);
		}
	}
	else
	{
		if (ft_strcmp(shell->autocompl->str, data) == 0)
		{
			free(shell->autocompl->str);
			ft_free_dlist(&shell->line); 
			ft_init_console(shell, shell->line, env);
			if (!shell->history->active)
			{
				tputs(shell->term->upstr, 1, ft_inputstr);
				tputs(shell->term->upstr, 1, ft_inputstr);
			}
			shell->autocompl->str = ft_strdup(data);
			i = -1;
			stat(data, &info_data);
			while (shell->autocompl->str[++i])
				ft_fill_back_dlst(shell->line, shell->autocompl->str[i], i + 2);
			if (S_ISDIR(info_data.st_mode))
				ft_fill_back_dlst(shell->line, '/', i + 2);
			return (1);
		}
	}
	return (0);
}

void    ft_put_antislash(t_shell *shell, char **after, char *result)
{
	char        *tmp;
	char        **tab_word;
	int         i;
	struct stat info;

	ft_put_antislash_one_word(shell);
	if (result)
	{
		tab_word = ft_strsplit2(result);
		i = ft_count_dtab(tab_word) - 1;
		ft_memset(&info, 0, sizeof(struct stat));
		lstat(tab_word[i], &info);
		if (S_ISDIR(info.st_mode))
		{
			tmp = ft_strjoin(*after, "/");
			free(*after);
			*after = ft_strdup(tmp);
			free(tmp);
		}
		ft_free_tab(tab_word);
	}
}

void	ft_autocompletion_bis(t_shell *shell, t_env *env)
{
	char        *before;
	char        *after;
	char        *result;
	int         limit;
	t_autocompl *begin;

	limit = 0;
	after = ft_after_antislash(shell->autocompl->str, &limit);
	before = ft_before_antislash(shell->autocompl->str, limit);
	result = ft_strjoin(before, after);
	ft_put_antislash(shell, &after, result);
	begin = shell->autocompl->current;
	while (begin)
	{
		if (ft_autocompl_simple(shell, begin->data, env) ||
				(after != NULL && ft_autocompl_complex(shell, begin->data, before, after, env)))
		{
			shell->auto_active = 0;
			tputs(shell->term->cdstr, 1, ft_inputstr);
			if (ft_count(shell->autocompl) == 1)							// If One word in list , don't display
				shell->multiauto_active = 0;
			break;
		}
		begin = begin->next;
	}
	free(before);
	free(after);
	free(result);
}

/*
 * * HEART FUNCTION AUTOCOMPLETION
 * *VARIABLE : shell->auto_active or multiauto_atcive if is active display word
 * 
 *  We reset all variable we need, transform list to str, add / in shell line if is shell 
 *  line is dir,fill list autocompletion initial current directory or open directory with shell line,
 *  if shell line look like same word in list autocompletion, we fill in new list from 
 *  ft_fill_same_word.
 */

void    ft_autocompletion(t_lineterm *end, t_shell *shell, t_env *env)
{
	(void)end;
	shell->autocompl->arrow = 0;
	if (ft_reset(shell, env))
		return ;
	else
	{
		shell->autocompl->str = ft_to_str(shell);
		ft_check_is_dir(shell);
		shell->auto_active = ft_init_autocompl(shell, shell->autocompl->str, env);
		shell->multiauto_active = ft_fill_same_word(shell, env);
		if (shell->autocompl->current && shell->autocompl->str)
			ft_autocompletion_bis(shell, env);
		else
			shell->auto_active = 0;
		if (ft_count(shell->autocompl) == 1)
		{
			shell->auto_active = 0;
			shell->multiauto_active = 0;
		}
		/*else if (ft_count(shell->autocompl) >= 50)
			shell->autocompl->possiblitie = 1;*/
	}
	if (ft_can_replace_glob(shell->autocompl->str) == 1)
		ft_replace_glob(shell, shell->autocompl->str, env);
}
