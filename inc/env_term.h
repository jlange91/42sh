#ifndef ENV_TERM_H
# define ENV_TERM_H

# include "sh21.h"

/*********************************************************************************/
/*INIT_ENV*/
t_env           *ft_init_env(char **env);

/********************************************************************************/
/*ENV*/
int             ft_setenv(const char *line, const char *value, t_env *env);
void			ft_unsetenv(char *line, t_env **env);
/********************************************************************************/
/*ENV_TOOLS*/
char            *ft_getpath(const char *line, const char *value);
void            ft_cpy_env(t_env **env, char *str, int i);
/********************************************************************************/
/*GETENV*/
char             *ft_getenv(char *line, t_env *env);

/********************************************************************************/
/*FREE*/
int             ft_free(char **str, int flag);
int             ft_free_str(char *s1, char *s2, int flag);

#endif
