#include "../../inc/built_in.h"

void	modif_var(char *elem, char *modif, t_env *env)
{
	/*int i;
	char *tmp;

	i = 0;
	tmp = NULL;*/
	while (env)
	{
		if (!ft_strncmp(env->line_env, elem, ft_strlen(elem)))
		{
			free(env->line_env);
			env->line_env = ft_free_join(elem, ft_strjoin("=", modif), 'R');
		}
		env = env->next;
	}
}

int		find_elem(t_env *env, char *elem)
{
	while(env)
	{
		if (ft_strncmp(elem, env->line_env, ft_strlen(elem)) == 0 && \
				env->line_env[ft_strlen(elem)] == '=')
			return (env->index);
		env = env->next;
	}
		return (-1);
}

int		count_index(t_env *env)
{
	int i;

	i = 0;
	while(env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

void	re_init_index(t_env **ev)
{
	t_env	*env;
	int		i;

	i = 0;
	env = *ev;
	while(env)
	{
		env->index = i;
		i++;
		env = env->next;
	}
}

char	*use_getcwd(void)
{
	char	*str;
	size_t	taille;

	taille = 100;
	if (!(str = (char*)malloc(sizeof(char) * (taille +1))))
		return (0);
	return (getcwd(str, taille));
}
