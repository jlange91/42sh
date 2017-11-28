# include "../inc/sh21.h"
# include "../inc/line_edition.h"

void			free_shell(t_shell *sh, t_termc *tsh)
{
	free_tab_2d(sh->env);
	free(sh->pwd);
	ft_free_all(tsh);
}

int		ft_singleton(int nb, int opt)
{
	static int ret = 0;

	if (opt == 1)
		ret = nb;
	return (ret);
}

void	ft_init_shell(t_shell *sh)
{
	sh->output = NULL;
	sh->input = NULL;
}

int     main(int ac, char **av, char **env)
{
	t_termc *tsh;
	t_shell sh;

    (void)ac;
    (void)av;
	tsh = NULL;
	ft_fill_env(&sh, env);
	tsh = init_termc(sh.env);
    ft_line_edition(tsh, sh);
	free_shell(&sh, tsh);
    return (0);
}
