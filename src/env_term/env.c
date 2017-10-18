#include "../../inc/env_term.h"
#include "../../inc/built_in.h"
int		ft_setenv(const char *line, const char *value, t_env *env)
{
	char	*path;
	char	*tmp;
    char    *str;

    path = NULL;
    tmp = NULL;
    tmp = ft_strjoin(line, "=");
	path = ft_getpath(line, value);
	if ((str = ft_getenv((char *)line, env)) != NULL)
	{
        free(str);
		while (env)
		{
			if (ft_strncmp(tmp, env->line_env, ft_strlen(tmp)) == 0)
			{
                free(env->line_env);
                env->line_env = ft_strdup(path);
                free(tmp);
                free(path);
				return (1);
			}
			env = env->next;
		}
	}
    else
        ft_cpy_env(&env, path, 0);
    free(tmp);
	free(path);
	return (0);
}

void	ft_unsetenv(char *line, t_env **begin_env)
{
	t_env	*tmp;
	t_env	*env;

	env = *begin_env;
	while(env->index != find_elem(env, line) - 1)
		env = env->next;
	tmp = env;
	env = env->next;
	tmp->next = env->next;
	free(env->line_env);
	free(env);
	env = NULL;
	re_init_index(begin_env);
}
