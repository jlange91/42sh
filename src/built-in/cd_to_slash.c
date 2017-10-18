#include "../../inc/built_in.h"
#include "../../inc/env_term.h"

char	*find_var(char *elem, t_env *env)
{
	while(env)
	{
		if (!ft_strncmp(env->line_env, elem, ft_strlen(elem)))
		{
			if (env->line_env[ft_strlen(elem)] == '=')
			return (ft_strchr(env->line_env, '=')+ 1);
		}
		env = env->next;
	}
	return (NULL);
}

void	road_to_slash2(t_env *env)
{
	char	*get_cwd;
	
	get_cwd = use_getcwd();
	ft_setenv("PWD", get_cwd, env);
	ft_unsetenv("OLDPWD", &env);
	free(get_cwd);
}

void	road_to_slash3(t_env *env)
{
	char	*get_cwd;

	chdir("/");
	get_cwd = use_getcwd();
	modif_var("PWD", get_cwd, env);
	free(get_cwd);
}

void	road_to_slash(t_env *env)
{
	char	*get_cwd;
	
	get_cwd = NULL;
	if (find_var("PWD", env))
	{
		if (find_var("OLDPWD", env))
		{
			modif_var("OLDPWD", find_var("PWD", env), env);
		}
		else
		{
			get_cwd = use_getcwd();
			ft_setenv("OLDPWD", get_cwd, env);
			free(get_cwd);
		}
	}
	if (!find_var("PWD", env))
			road_to_slash2(env);
	road_to_slash3(env);
}
