#ifndef GLOBBING_H
# define GLOBBING_H

# include "sh21.h"

/*******************************************************************/
/*INIT_GLOB.C*/
int    ft_parse_glob(char *line, t_glob **glob, t_env *env);

/*******************************************************************/
/*GET_GLOB.C*/
int    ft_get_glob(t_glob **glob, char **str_tab, t_env *env);
int     ft_glob_here(char *str);

/*******************************************************************/
/*RESULT_GLOB.C*/
char    **ft_result(t_env *env, t_glob *glob, char **str_tab);
/*******************************************************************/

/*******************************************************************/
/*MATCH.C*/
int		ft_match(char *pattern, char *word);
/*******************************************************************/

/*******************************************************************/
/*MATCH_CHUNK.C*/
int	ft_match_chunk(char *chunk, char **word, int i);
/*******************************************************************/

/*******************************************************************/
/*TOOL_MATCH_AND_CHUNK.C*/
char	*ft_init_var(int *neg, int *count, int *match, char *word);
void	ft_move_letter_and_count(char **chunk_orig, int *count, char **tmp_orig, int flag);
/*******************************************************************/

/*******************************************************************/
/*REPLACE*/
int		ft_can_replace_glob(char *line);
void	ft_replace_glob(t_shell *shell, char *line, t_env *env);
/*******************************************************************/

#endif
