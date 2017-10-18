#include "../../inc/built_in.h"
#include "../../inc/line_edition.h"
void	ft_error_unsetenv(t_cmd *cmd)
{
	if (ft_count_dtab(cmd->str_t) < 2)
	{
		ft_putchar('\n');
		ft_putstr_fd("unsetenv : not enough arguments", 2);
	}
}

void del_elem_env(t_env **begin_env, t_cmd *cmd)
{

	t_env	*tmp;
	t_env	*env;

	env = *begin_env;
	while(env->index != find_elem(env, cmd->str_t[1]) - 1)
		env = env->next;
	tmp = env;
	env = env->next;
	tmp->next = env->next;
	free(env->line_env);
	free(env);
	env = NULL;
	re_init_index(begin_env);
}

void	ft_cmd_unsetenv(t_cmd *cmd, t_env *env)
{
	/*char *tmp;
	tmp = NULL;*/
	if (ft_count_dtab(cmd->str_t) < 2)
	{
		ft_error_unsetenv(cmd);
		return ;
	}
	if (find_elem(env, cmd->str_t[1]) == -1)
		return ;
	del_elem_env(&env, cmd);
}
