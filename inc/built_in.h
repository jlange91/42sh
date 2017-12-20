#ifndef BUILT_IN_H
# define BUILT_IN_H

#include "sh21.h"

/********************************/
/*            builtins          */
/********************************/

void		ft_echo(char **av);
void		ft_cd(t_cmd *cmd);
void		ft_cd_l(t_cmd *cmd, char *path);
void		ft_cd_p(t_cmd *cmd, char *path);
void		ft_env(t_cmd *cmd);
int			env_skip_name_value(char **av, char ***env);
void		ft_prepare_setenv(t_cmd *cmd);
char		**ft_setenv(char *name, char *value, char **env);
void		ft_prepare_unsetenv(t_cmd *cmd);
char		**ft_unsetenv(char *name, char **env);
void		ft_pwd(t_cmd *cmd);
int			display_octal(char *str);
int			display_hexa(char *str);
void		prepare_export(t_cmd *cmd);

/*
* * HISTORY_B
*/

int         history(t_cmd *cmd);

/*
* * HISTORY_B2
*/

void        ft_opt_a(char *av2, t_history *begin, hlist *hist);
void        ft_opt_w(char *av2, t_history *begin, hlist *hist);
void        ft_opt_r(char *av2, t_history *begin, hlist *hist);
int         ft_opt_p(char **av, hlist *hist);
int         ft_opt_s(char **av, hlist *hist);

#endif
