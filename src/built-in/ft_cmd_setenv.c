#include "../../inc/built_in.h"
#include "../../inc/env_term.h"

void	ft_error_setenv(t_cmd *cmd)
{
	if (ft_count_dtab(cmd->str_t) < 4)
	{
		ft_putchar('\n');
		ft_putstr_fd("setenv : not enough arguments", 2);
	}
	if (ft_count_dtab(cmd->str_t) > 4)
	{
		ft_putchar('\n');
		ft_putstr_fd("setenv : too many arguments", 2);
	}
}

void modify_elem_env(t_env *env, t_cmd *cmd, int index)
{
		if (ft_atoi(cmd->str_t[3]) != 0)
		{
			while (env->index != index)
				env = env->next;
			env->line_env = ft_strdup(ft_strjoin \
			(cmd->str_t[1], ft_strjoin("=", cmd->str_t[2])));
		}
}

void	ft_create_elem(t_env *env, t_cmd *cmd)
{
	char *path;

	path = ft_strjoin(cmd->str_t[1], ft_strjoin("=", cmd->str_t[2]));
    ft_cpy_env(&env, path, count_index(env));
}
void ft_cmd_setenv(t_cmd *cmd, t_env *env)
{
	int		index;
	index = -1;
	if (ft_count_dtab(cmd->str_t) != 4)
		ft_error_setenv(cmd);
	else
	{
		index = find_elem(env, cmd->str_t[1]);
		if (index != -1)
			modify_elem_env(env, cmd, index);
		else
		ft_create_elem(env, cmd);
	}
}
