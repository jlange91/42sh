#include "../../inc/env_term.h"

char    *ft_getenv(char *line, t_env *env)
{
    char    *tmp;

    tmp = NULL;
    tmp = ft_strjoin(line, "=");
    if (tmp)
    {
        while (env)
        {
            if (ft_strncmp(tmp, env->line_env, ft_strlen(tmp)) == 0)
            {
                env->getenv_path = ft_strdup(env->line_env + ft_strlen(tmp));
                free(tmp);
                return (env->getenv_path);
            }
            env = env->next;
        }
		free(tmp);
    }
    return (NULL);
}
