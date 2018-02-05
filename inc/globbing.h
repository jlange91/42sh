/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 17:32:23 by stvalett          #+#    #+#             */
/*   Updated: 2018/01/30 16:20:57 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBBING_H
# define GLOBBING_H

# include "sh21.h"

/*
**MAIN_GLOB
*/

char	*ft_glob(char *word);

/*
**RESULT_GLOB
*/

char	*ft_resglob(t_glob *glob, int star, char **str);

/*
**CHECK_GLOB
*/

int		ft_syntax_braces(char *word);
int		ft_syntax_bracket(char *word);
int		ft_glob_here(char *str);
int		ft_only_star(char *word);

/*
**TOOLS_GLOB
*/

void	ft_free_glob(t_glob *glob, int len);
void	ft_save_word(t_glob *glob, char **str, int len);
char	**ft_add_slash(char *word, char c);
char	*ft_add_b_slash(char *file);
void	freeall(char *pwd, char **res, char **s_tab, t_glob *glob);

/*
**OPEN_GLOB
*/

char	**ft_open(char *pwd, char *pattern, int star, int flag);

/*
**MATCH
*/

int		ft_match(char *pattern, char *word);

/*
**MATCH_CHUNK
*/

int		ft_match_chunk(char *chunk, char **word, int i);

/*
**TOOL_MATCH_AND_CHUNK
*/

t_glob	*ft_free_or_not(char **res, char **s_tab, t_glob *glob, int len);
void	ft_move_index(char **chunk_orig, int *count, char **tmp_orig, int flag);
char	*ft_init_var(int *neg, int *count, int *match, char *word);
int		ft_escape_or_end(char *tmp, char **chunk, int *count, int *escape);
int		ft_skip_or_leave(char **tmp, char **chunk, int *count, int *escape);

#endif
