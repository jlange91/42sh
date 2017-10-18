#include "../../inc/built_in.h"
#include "../../inc/env_term.h"

static void ft_init_tab_built(const char *tab_built[7])
{
    tab_built[0] = "exit";
    tab_built[1] = "env";
    tab_built[2] = "cd";
    tab_built[3] = "echo";
    tab_built[4] = "setenv";
    tab_built[5] = "unsetenv";
    //tab_built[6] = "history";*/
}

static  void ft_init_built_funct(t_built funct[7])
{
    funct[0] = ft_cmd_exit;
    funct[1] = ft_cmd_env;
    funct[2] = ft_cmd_cd;
    funct[3] = ft_cmd_echo;
    funct[4] = ft_cmd_setenv;
    funct[5] = ft_cmd_unsetenv;
    //funct[6] = ft_cmd_unsetenv;*/
}

int    ft_check_builtin(char *str, t_env *env, t_cmd *cmd)
{
    const char      *tab_built[7];
    static t_built  fnct[7];
    int             i;

    ft_init_built_funct(fnct);
    ft_init_tab_built(tab_built);
    i = -1;

	if (env->line_str)
	{
	if (ft_dquote(env->line_str))
		ft_dodquote(&env);
	if (ft_quote(env->line_str))
		ft_doquote(&env);
	}
	while (++i < 6)
    {
        if (ft_strcmp(tab_built[i], str) == 0)
        {
            fnct[i](cmd, env);
            if (i == 0)
                return (-1);
            return (1);
        }
    }
    return (0);
}
