#ifndef BUILT_IN_H
# define BUILT_IN_H

#include "sh21.h"

/*TOOLS*/
int		find_elem(t_env *env, char *elem);
int		count_index(t_env *env);
void	re_init_index(t_env **env);
void	modif_var(char *elem, char *modif, t_env *env);
char	*use_getcwd(void);
char	*new_path(char *str, t_env *env);
void	early_test(t_env *env);
int		fast_test(char *str, char *tmp);
void	permute(char *tmp, t_env *env);
char	*transform_char_point(char *str);
char	*find_var(char *elem, t_env *env);

typedef void(*t_built)(t_cmd *cmd, t_env *env);

/*CD*/
void    ft_cmd_cd(t_cmd *cmd, t_env *env);
void	cd_to_oldpwd(t_env *env);
void	road_to_slash(t_env *env);
void	ft_go_to_home(t_env *env);
void	ft_error_of_cd(char *elem, int error);
int		find_error(char *elem);
void	cd_to_dir(char *dir, t_env *env);

/*ENV*/
void    ft_cmd_env(t_cmd *cmd, t_env *env);

/*BUILT*/
int     ft_check_builtin(char *str, t_env *env, t_cmd *cmd);

/*BUILT_UTILS*/
void    ft_cmd_echo(t_cmd *cmd, t_env *env);
void    ft_cmd_exit(t_cmd *cmd, t_env *env);
void	ft_cmd_setenv(t_cmd *cmd, t_env *env);
void	ft_cmd_unsetenv(t_cmd *cmd, t_env *env);
void	ft_print_env(t_env *env);

int		ft_dquote(char *str);
int		ft_quote(char *str);
void	ft_dodquote(t_env **env);
void	ft_doquote(t_env **env);

#endif
