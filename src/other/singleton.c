#include "../../inc/sh21.h"

char	**ft_var_env(char **arg)
{
	static char **env = NULL;

	if (arg)
		env = arg;
	return (env);
}

char	**ft_var_var(char **arg)
{
	static	char **var = NULL;

	if (arg)
		var = arg;
	return (var);
}

char	*ft_var_pwd(char *arg)
{
	static char *pwd = NULL;

	if (arg)
		pwd = arg;
	return (pwd);
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