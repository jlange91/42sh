#ifndef BUILT_IN_H
# define BUILT_IN_H

#include "sh21.h"

/********************************/
/*            builtins          */
/********************************/

void		ft_echo(char **av);
void		ft_cd(t_cmd *cmd, int fast);
int 		ft_cd_l(char *path, int opt);
int 		ft_cd_p(char *path, int opt);
int			ft_try_cdpath(char *path, char **env, int opt);
void		ft_env(t_cmd *cmd);
int			env_skip_name_value(char **av, char ***env);
void		ft_prepare_setenv(t_cmd *cmd);
char		**ft_setenv(char *name, char *value, char **env);
void		ft_prepare_unsetenv(t_cmd *cmd);
char		**ft_unsetenv(char *name, char **env);
void		ft_pwd(char **av);
int			display_octal(char *str);
int			display_hexa(char *str);
void		prepare_export(t_cmd *cmd);
void		ft_help(void);

/*
* * HISTORY_B
*/

int         history(t_cmd *cmd);
int			ft_end(char *av1, int flag);

/*
** HISTORY_B2
*/

void        ft_opt_a(char *av2, t_history *begin, hlist *hist);
void        ft_opt_w(char *av2, t_history *begin, hlist *hist);
void        ft_opt_r(char *av2, t_history *begin, hlist *hist);
int         ft_opt_p(char **av, hlist *hist);
int         ft_opt_s(char **av, hlist *hist);

/*
** HISTORY_BCHECK
*/
int 		ft_check_option(char *av1, char *av2);
int 		ft_error_history(char *av, int flag);

/*
**TOOLS_HSITORY
*/

int		ft_display_history(hlist *histlist);
void 	ft_del_elem_history_split(int index, hlist *histlist);
int		ft_del_elem_history(char *av, hlist *histlist, int flag);
int		ft_split_error_hist(int flag);
int		ft_split_exec(char *av1, int i, char **av, hlist *hist);

#endif
