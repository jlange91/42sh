# include "../inc/sh21.h"
# include "../inc/line_edition.h"

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

int     main(int ac, char **av, char **env)
{
	t_termc *tsh;
	t_cmd cmd;

    (void)ac;
    (void)av;
	tsh = NULL;
	ft_fill_env(&cmd, env);
	tsh = init_termc(cmd.env);
    ft_line_edition(tsh, cmd);
	free_shell(&cmd, tsh);
    return (0);
}
