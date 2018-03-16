/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 16:18:03 by vmartins          #+#    #+#             */
/*   Updated: 2018/01/25 12:42:09 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "sh21.h"

/*
**builtins
*/

void	ft_echo(char **av);
void	ft_cd(t_cmd *cmd, int fast);
int		ft_cd_l(char *path, int opt);
int		ft_cd_p(char *path, int opt);
int		ft_try_cdpath(char *path, char **env, int opt);
void	ft_env(t_cmd *cmd);
int		env_skip_name_value(char **av, char ***env);
void	ft_prepare_setenv(t_cmd *cmd);
char	**ft_setenv(char *name, char *value, char **env);
void	ft_prepare_unsetenv(t_cmd *cmd);
char	**ft_unsetenv(char *name, char **env);
void	ft_pwd(char **av);
int		display_octal(char *str);
int		display_hexa(char *str);
void	prepare_export(t_cmd *cmd);
void	ft_help(void);
int		ft_menu_builtins(t_cmd *cmd, t_termc *tsh);
void	ft_exit(t_cmd *cmd);

/*
**HISTORY_B
*/

int		history(t_cmd *cmd);
int		ft_end(char *av1, int flag);

/*
**HISTORY_B2
*/

void	ft_opt_a(char *av2, t_history *begin, t_hist *hist);
void	ft_opt_w(char *av2, t_history *begin, t_hist *hist);
void	ft_opt_r(char *av2, t_history *begin, t_hist *hist);
int		ft_opt_p(char **av, t_hist *hist);
int		ft_opt_s(char **av, t_hist *hist);

/*
**HISTORY_BCHECK
*/

int		ft_check_option(char *av1, char *av2);
int		ft_error_history(char *av, int flag);

/*
**TOOLS_HISTORY
*/

int		ft_display_history(t_hist *histlist);
void	ft_del_elem_history_split(int index, t_hist *histlist);
int		ft_del_elem_history(char *av, t_hist *histlist, int flag);
int		ft_split_error_hist(int flag);
int		ft_split_exec(char *av1, int i, char **av, t_hist *hist);

#endif
