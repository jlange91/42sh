#ifndef TREE_H
# define TREE_H

# include "sh21.h"

/****************************************************************/
/*TREE.C*/

void        ft_parse(t_lexer *lexer, t_tree **root);
t_tree  *ft_get_cmdline(t_token *current);

/****************************************************************/
/*UTILS_TREE*/

t_tree  *ft_init_tree(t_token *tmp, t_tree *job, t_tree *cmd, int type);
int     ft_find_token(t_token **current, int type, t_token **tmp);


void    ft_free_ast(t_tree *root);

/****************************************************************/
/*JOB*/
t_tree  *ft_get_job(t_token **current);
t_tree  *ft_greater_cmd(t_token **current);
t_tree  *ft_get_job_pipe(t_token **current);
t_tree  *ft_otherargv(t_token **current);
t_tree  *ft_job_to_cmd(t_token **current);

#endif
