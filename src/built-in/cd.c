#include "../../inc/built_in.h"
#include "../../inc/env_term.h"


void	ft_go_to_home(t_env *env)
{
    char *get_cwd;
	
	if (!find_var("HOME", env))
		ft_putendl_fd("cd : HOME not set", 2);
	else if (!find_var("PWD", env) && !find_var("HOME", env))
		ft_putendl_fd("cd : HOME not set", 2);
	else if (chdir(find_var("HOME", env)) == -1)
		ft_error_of_cd(find_var("HOME", env), \
			find_error(find_var("HOME", env)));
	else if (!find_var("PWD", env))
	{
		get_cwd = use_getcwd();
		ft_setenv("PWD", get_cwd, env);
		free(get_cwd);
	}
	else
	{
		chdir(find_var("HOME", env));
		modif_var("OLDPWD", find_var("PWD", env), env);
		get_cwd = use_getcwd();
		modif_var("PWD", get_cwd, env);
		free(get_cwd);
	}
}

void	cd_to_oldpwd(t_env *env)
{
	char *get_cwd;
	
	if (find_var("OLDPWD", env) == NULL)
		ft_putendl_fd("cd : OLDPWD not set", 2);
	else if (find_var("PWD", env) == NULL)
	{
		chdir(find_var("OLDPWD", env));
		ft_putchar('\n');
		ft_putstr(find_var("OLDPWD", env));
		ft_unsetenv("OLDPWD", &env);
	}
	else
	{
		ft_putstr(find_var("OLDPWD", env));
		chdir(find_var("OLDPWD", env));
		get_cwd = use_getcwd();
		modif_var("OLDPWD", find_var("PWD", env), env);
		modif_var("PWD", get_cwd, env);
		free(get_cwd);
	}
}

void    ft_parse_cd(char *str, t_env *env)
{
    if (ft_strcmp(str, "-") == 0 && ft_strlen(str) == 1)
		cd_to_oldpwd(env);
	else if (!ft_strcmp(str, "--") || !ft_strcmp(str, "~") || \
			!ft_strcmp(str, "$HOME"))
		ft_go_to_home(env);
	else if (ft_strlen(str) == 1 && str[0] == '/')
		road_to_slash(env);
	else
		cd_to_dir(transform_char_point(str), env);
}

void    ft_cmd_cd(t_cmd *cmd, t_env *env)
{

    if (ft_count_dtab(cmd->str_t) == 1)
		ft_go_to_home(env);
	if (ft_count_dtab(cmd->str_t) >= 2)
		ft_parse_cd(cmd->str_t[1], env);
}
