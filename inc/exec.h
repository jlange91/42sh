#ifndef EXEC_H
# define EXEC_H

# include "sh21.h"

/********************************************************/
/*EXEC.C*/
int    ft_execute(t_tree *root, t_env *env, t_lexer *lexer);

/********************************************************/

/********************************************************/
/*CMD.C*/
int     ft_cmd_exe(char *str, t_cmd *cmd, t_env *env);

/********************************************************/

/********************************************************/
/*UTIL_CMD.C*/
void    ft_free_all_cmd(char **str1, char **str2);
char    **ft_cmd_to_tab(t_cmd *cmd);
char    **ft_env_to_tab(t_env *env);
#endif
