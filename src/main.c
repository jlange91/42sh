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

int		ft_singleton(int nb, int opt)
{
	static int ret = 0;

	if (opt == 1)
		ret = nb;
	return (ret);
}

t_shell		*ft_ret_sh(t_shell *arg)
{
	static t_shell *sh = NULL;

	if (arg)
		sh = arg;
	return (sh);
}

static void  ft_free_free(t_termc *sh)
{
	free(sh->line_shell);
	ft_free_dlist(&sh->line);
	ft_free_history(sh->history);
}

char	**ft_var_env(char **arg)
{
	static char **env = NULL;

	if (arg)
		env = arg;
	return (env);
}

char	*ft_var_pwd(char *arg)
{
	static char *pwd = NULL;

	if (arg)
		pwd = arg;
	return (pwd);
}

void	ft_exec_all_cmd(t_cmd *cmd)
{
	int		ret;
	int		val;

	ret = 0;
	val = 1;
	while (cmd)
	{
		if (val == 1)
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
	ft_ret_sh(&sh);
	ft_ret_tsh(&tsh);
	while (42)
	{
		signal(SIGINT, ft_handle_signal);
		ft_fill_history(tsh);
		ft_fill_line(tsh);
		sh.line = ft_strdup(tsh->line_shell);
		ft_free_free(tsh);
		ft_replace(&sh);		
		cmd = ft_fill_cmd(sh.line, 0, 0);
		free(sh.line);
		ft_exec_all_cmd(cmd);
		ft_end_term(tsh);
		ft_free_cmd(cmd);
	}
	free_shell(tsh);
    return (0);
}
