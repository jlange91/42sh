#include "../../inc/built_in.h"
#include "../../inc/env_term.h"

void ft_print_env(t_env *env)
{
    if (env)
    {
        ft_putchar('\n');
        while (env)
        {
           ft_putendl(env->line_env);
            env = env->next;
        }
    }
}

void    ft_cmd_env(t_cmd *cmd, t_env *env)
{
	int i;

	 i = 0;
	while (cmd->str_t[i])
	{
		ft_putendl(cmd->str_t[i]);
		i++;
	}
    if (ft_count_dtab(cmd->str_t) > 1)
        ft_putendl("LOT ARGV CMD ENV");
    else
        ft_print_env(env);
}
