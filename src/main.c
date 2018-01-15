# include "../inc/sh21.h"
# include "../inc/line_edition.h"
#include "../inc/built_in.h"
#include "../inc/globbing.h"
#include "../inc/quote.h"

void			free_shell(t_termc *tsh)
{
	free_tab_2d(ft_var_env(NULL));
	free(ft_var_pwd(NULL));
	ft_free_all(tsh);
}

static void  ft_free_free(t_termc *tsh)
{
	free(tsh->line_shell);
	ft_free_dlist(&tsh->line);
	ft_free_history(tsh->histmp);
}

void	ft_exec_all_cmd(t_cmd *cmd)
{
	int		ret;
	int		val;

	ret = 0;
	val = 1;
	while (cmd)
	{
		if (val == 1 && cmd->l_op != 4)
			ret = ft_line_edition(cmd);
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

void	ft_free_cmd(t_cmd *cmd)
{
	t_cmd *tmp;

	while (cmd)
	{
		free_tab_2d(cmd->av);
		free(cmd->line);
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}

int     main(int ac, char **av, char **env)
{
	t_termc	*tsh;
	t_cmd	*cmd;
	t_shell	sh;

    (void)ac;
    (void)av;
	tsh = NULL;
	ft_fill_env(env);
	tsh = init_termc(ft_var_env(NULL));
	ft_memset(&sh, 0, sizeof(sh));
	ft_ret_sh(&sh);
	ft_ret_tsh(&tsh);
	ft_init_signal(); 			//NEW GESTIONNAIRE SIGNAL
	while (42)
	{
		ft_fill_history(tsh);
		ft_fill_line(tsh);
		sh.line = ft_strdup(tsh->line_shell);
		ft_free_free(tsh);
		ft_result_replace(&sh);
		if (sh.line == NULL || tsh->repl)
			continue ;
		if (ft_check_cmd(&sh) || ft_check_redir(&sh))
		{
			free(sh.line);
			continue ;
		}
		if (tsh->save_line && ft_strlen(tsh->save_line) > 1)
			ft_add_tmp_history(tsh, tsh->save_line);
		ft_strdel(&tsh->save_line);
		cmd = ft_fill_cmd(sh.line, 0, 0);
		free(sh.line);		
		ft_exec_all_cmd(cmd);
		ft_free_cmd(cmd);
		
	}
	free_shell(tsh);
	ft_free_hash();
	
    return (0);
}
