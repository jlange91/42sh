#ifndef BUILT_IN_H
# define BUILT_IN_H

#include "sh21.h"

/********************************/
/*            builtins          */
/********************************/

void		ft_echo(char **av);
void		ft_cd(t_shell *sh);
void		ft_cd_l(t_shell *sh, char *path);
void		ft_cd_p(t_shell *sh, char *path);
void		ft_env(t_shell *sh);
int			env_skip_name_value(char **av, char ***env);
void		ft_prepare_setenv(t_shell *sh);
char		**ft_setenv(char *name, char *value, char **env);
void		ft_prepare_unsetenv(t_shell *sh);
char		**ft_unsetenv(char *name, char **env);
void		ft_pwd(t_shell *sh);
int			display_octal(char *str);
int			display_hexa(char *str);
void		prepare_export(t_shell *sh);

#endif
