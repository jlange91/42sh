#include "../../inc/built_in.h"
#include "../../inc/env_term.h"

char	*new_path(char *str, t_env *env)
{
	char	*tmp;
	char	*tmp2;

	tmp2 = NULL;
	if (str[0] == '/')
		tmp = ft_strdup(str);
	else if (find_var("PWD", env))
		tmp = ft_free_join(find_var("PWD", env), ft_strjoin("/", str), 'R');
	else
	{
		tmp2 = use_getcwd();
		tmp = ft_free_join(tmp2, ft_strjoin("/", str), 'B');
	}
	return (tmp);
}

void	early_test(t_env *env)
{
	char *tmp;

	tmp = NULL;
	if (env->line_env == NULL)
	{
		tmp = use_getcwd();
		ft_setenv("PWD", tmp, env);
		free(tmp);
	}
}

int		fast_test(char *str, char *tmp)
{
	if (str[0] != '$' && chdir(tmp) == -1)
	{	
		ft_error_of_cd(str, find_error(str));
		free(tmp);
		return (1);
	}
	return (0);
}

void	permute(char *tmp, t_env *env)
{
	char	*get_cwd;

	(void)tmp;
	if (!find_var("OLDPWD", env))
		ft_setenv("OLDPWD", find_var("PWD", env), env);
	modif_var("OLDPWD", find_var("PWD", env), env);
	chdir(tmp);
	get_cwd = use_getcwd();
	modif_var("PWD", get_cwd, env);
	free(get_cwd);
	free(tmp);
	(chdir("/Users/stvalett/projet/42sh/symb"));
//	get_cwd = use_getcwd();
	modif_var("PWD", "/Users/stvalett/projet/42sh/symb", env);
//	free(get_cwd);
//	free(tmp);
}

char	*transform_char_point(char *str)
{
	char	*new_tmp;

	int		i;

	i = 2;
	new_tmp = ft_strdup("../");
	if (str[0] && str[1] == '.')
	{
		while(str[i])
		{
			if (str[i] != '.')
				return (str);

			new_tmp = ft_strdup(ft_free_join(new_tmp, ft_strjoin("..", "/"), 'R'));
			i++;
		}
		free(str);
		str = ft_strdup(new_tmp);
		free(new_tmp);
		return (str);
	}
	return (str);
}
