# include "../inc/sh21.h"
# include "../inc/line_edition.h"
#include "../inc/built_in.h"
#include "../inc/globbing.h"
#include "../inc/quote.h"

void			free_shell(t_cmd *cmd, t_termc *tsh)
{
	free_tab_2d(cmd->env);
	free(cmd->pwd);
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

int     main(int ac, char **av, char **env)
{
	t_termc *tsh;
	t_cmd cmd;
	t_shell sh;

    (void)ac;
    (void)av;
	tsh = NULL;
	ft_fill_env(&sh, env);
	tsh = init_termc(sh.env);
	ft_ret_sh(&sh);
	ft_ret_tsh(&tsh);
	while (42)
	{
		signal(SIGINT, ft_handle_signal);
		cmd.env = sh.env;
		cmd.pwd = sh.pwd;
		ft_fill_history(tsh);
		ft_fill_line(tsh);
		sh.line = ft_strdup(tsh->line_shell);
		ft_free_free(tsh);
		ft_replace(&sh);
		write(1, "\n", 1);
		cmd.line = ft_strdup(sh.line); // a changer plus tard
		//while () plus tard while ligne de commande
	    ft_line_edition(tsh, &cmd);
		sh.env = cmd.env;
		sh.pwd = cmd.pwd;
		free(cmd.line);
		free(sh.line);

	}
	free_shell(&cmd, tsh);
    return (0);
}
