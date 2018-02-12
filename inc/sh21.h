/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh21.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 17:03:20 by stvalett          #+#    #+#             */
/*   Updated: 2018/01/31 15:05:53 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH21_H
# define SH21_H

# include <stdio.h>
# include <sys/wait.h>
# include <pwd.h>
# include <assert.h>
# include <termios.h>
# include "../libft/include/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/stat.h>
# include "hash.h"

# define PATH_MAX 2048

/*
**FROM DIRECTORY LINE_EDITION
**DC = Del one caractere in screen
**CL = Clean all screen and put cursor on the top left
**CM = Move cursor %1 line , %1 col
**CB = Clean begin line until end cursor
**LE = Move cursor one caractere on left
**ND = Move cursor one caractere on right
**DL = Delete the line
**DO = Down cursor
**UP = Up cursor
**CD = clean the screen since cursor to end term
**VI = Cursor invisible
**VE = Cursor visible
**CE = Clean line
*/

typedef struct	s_term
{
	char				*dcstr;
	char				*clrstr;
	char				*cmstr;
	char				*cbstr;
	char				*lestr;
	char				*ndstr;
	char				*dlstr;
	char				*dostr;
	char				*upstr;
	char				*cdstr;
	char				*vistr;
	char				*vestr;
	char				*cestr;
	char				bp[2048];
	char				area[2048];
	struct termios		old_termios;
	struct termios		term;
}				t_term;

typedef struct	s_history
{
	int					index;
	int					new;
	int					print;
	char				*data;
	struct s_history	*next;
	struct s_history	*prev;
}				t_history;

typedef struct	s_hist
{
	int					ecrase_hist;
	char				*pwd;
	t_history			*begin;
	t_history			*current;
	t_history			*end;
}				t_hist;

typedef struct	s_console
{
	size_t				total_line;
	size_t				char_pos;
}				t_console;

typedef struct	s_lineterm
{
	char				c;
	int					under;
	int					s_pos;
	int					index;
	struct s_lineterm	*next;
	struct s_lineterm	*prev;
}				t_lineterm;

typedef	struct	s_dlist
{
	int					lnk_before;
	int					last;
	t_lineterm			*begin;
	t_lineterm			*end;
}				t_dlst;

typedef struct	s_key
{
	int					underline;
	int					cl;
	int					k_tab;
}				t_keyflag;

typedef struct	s_var_auto
{
	int					row;
	int					len;
	int					ttl_jump;
	int					down;
}				t_var_auto;

typedef struct	s_autocompl
{
	char				*data;
	int					index;
	struct s_autocompl	*next;
	struct s_autocompl	*prev;
}				t_autocompl;

typedef struct	s_senti_auto
{
	char				*str;
	int					finish;
	int					jump;
	int					max_len;
	int					row;
	int					col;
	int					pages;
	int					more_pages;
	int					nbr_word;
	int					updaterow;
	int					arrow;
	int					clr_yes;
	int					can_print;
	int					possiblitie;
	t_autocompl			*begin;
	t_autocompl			*current;
	t_autocompl			*end;
}				t_auto;

typedef struct	s_termc
{
	int					quotes;
	int					quote_no;
	int					hdoc;
	int					auto_active;
	int					multiauto_active;
	int					len_prompt;
	int					repl;
	int					sigint;
	int					hour;
	int					path;
	int					prompt;
	int					host;
	int					linep;
	char				*line_shell;
	char				*save_line;
	char				**color;
	char				*replace;
	t_auto				*autoc;
	t_dlst				*line;
	t_dlst				*line_dup;
	t_hist				*histmp;
	t_hist				*histlist;
	t_term				*term;
	t_console			*console;
	t_keyflag			*keyflag;
}				t_termc;

/*
**FROM DIRECTORY GLOBBING
*/

typedef struct	s_glob
{
	char				**s_tab;
	char				**res;
	char				*path;
	int					len;
}				t_glob;

typedef struct	s_cmd
{
	char				*line;
	char				**av;
	int					ac;
	char				*hrdc;
	int					load;
	char				**var;
	int					l_op;
	int					r_op;
	struct s_cmd		*next;
}				t_cmd;

typedef struct	s_shell
{
	char				*line;
	t_hash				hash[SIZEH];
	char				*hrdcpwd;
}				t_shell;

typedef struct	s_redir
{
	int					in;
	int					out;
	int					type;
	int					close;
}				t_redir;

void			ft_perror(char *str, int error, char *str2);

/*
**replace
*/

void			ft_result_replace(t_shell *sh);
void			ft_replace(t_shell *sh);
void			ft_replace_dollar(t_shell *sh, int save);
void			ft_replace_tilde(t_shell *sh, int save);
char			*ft_replace_line(char *str1, char *value, char *str2);
char			*ft_add_escape(char *str);

/*
**REPLACE_HIST
*/

void			ft_replace_exp_hist(t_termc *tsh);
void			*ft_skip(t_lineterm *tmp, int len);
int				ft_find3(t_termc *tsh, t_lineterm *begin, int *count);
int				ft_find2(t_termc *tsh, t_lineterm *begin, int *count);
int				ft_find(t_termc *tsh, t_lineterm *begin, int *count);

/*
**TOOL_REPLACE
*/

void			ft_cpy_to_line(char *data, t_termc *tsh);
void			ft_dupdlnk(t_dlst *line, t_dlst *tmp);
void			ft_freedlnk(t_dlst *line);
void			push_dupdlst(t_dlst *new, t_lineterm *line);
int				ft_word_here(t_lineterm *begin, char *word);

/*
**TOOL_REPLACE2
*/

void			ft_join_all(char *word, char **line_tmp, int ret);
void			ft_add_space(char **line, char **s_line, char *word);

/*
**REPLACE_GLOB
*/

void			ft_replace_glob_exp(t_termc *tsh, t_lineterm *end);

/*
**exec
*/

void			ft_exec(t_cmd *cmd, char **av, char **env);
void			ft_exec_pipe(char **av, char **env);
int				ft_exit_exec(t_cmd *cmd, int ret);
int				ft_builtin_and_exec(t_cmd *cmd);

/*
**singleton.C
*/

char			**ft_var_env(char **arg);
char			**ft_var_var(char **arg);
char			*ft_var_pwd(char *arg);
int				ft_singleton(int nb, int opt);
t_shell			*ft_ret_sh(t_shell *arg);

/*
**singleton2.C
*/

char			**ft_var_local(char **arg);
char			*ft_var_hrdcpwd(char *arg);
t_termc			*ft_ret_tsh(t_termc **arg);
int				ft_ret_down(int len);

/*
**other
*/

void			signal_sigint();
void			ft_display_env(char **env);
void			ft_chdir_error(char *path);
char			*ft_getenv(const char *name, char **env);
void			ft_fill_env(char **env);
char			**ft_replace_env(char **new_env, char **old_env);
char			*ft_remove_useless_path(char *str);
char			*ft_replace_str(char *new, char *old);
char			**ft_cp_env(char **env);
void			ft_charcat(char *str, char c);
void			free_tab_2d(char **tab);
int				tab_2d_len(char **tab);
char			**rapid_set(char *input, char **env, int j);
void			export_no_eq(t_cmd *cmd, int i);
int				export_with_eq(t_cmd *cmd, int i);
char			**load_env(char **env);
void			export_flagb(t_cmd *cmd, int i);
void			replace_elem(char *compare, char *input, char **env);
int				check_correct_arg(t_cmd *cmd, int i);
void			export_flag_b(t_cmd *cmd, int i);
int				only_p(t_cmd *cmd);
int				check_pattern(char *str);
void			ft_display_export(char	**var);
int				ft_skip_useless(char *line);
void			ft_cmd(t_cmd *cmd);
int				ft_skip_quote(char *str);
int				ft_skip_dquote(char *str);
t_shell			*ft_ret_sh(t_shell *arg);
char			**ft_var_var(char **arg);
void			ft_theme(t_cmd *cmd, t_termc *tsh);
void			ft_theme_hour(char *str, t_termc *tsh);
void			ft_theme_host(char *str, t_termc *tsh);
void			ft_theme_prompt(char *str, t_termc *tsh);
void			ft_theme_path(char *str, t_termc *tsh);
void			ft_theme_global(char *str, t_termc *tsh);
void			change_all_color(t_termc *tsh, int color);
void			prepare_setlocal(t_cmd *cmd);
char			**ft_var_local(char **arg);
int				p_here(t_cmd *cmd);
char			**init_local(void);
void			add_each(t_cmd *cmd, int i, char *tmp);
void			basic_replace(char *compare, char *input, char **env);
void			check_env_export(char *tmp, char *str, int index);
int				place_me(t_cmd *cmd);
void			update_local(int i, int j);
void			update_export(int i, int j);
int				ft_backslash_word(char *line);

/*
**redirection
*/

char			*ft_ret_word(char *line);
void			ft_fill_word(char *line, char *word);
int				ft_redirection(t_cmd *cmd);
void			ft_remove_redirection();
int				ft_count_char_word(char *line);
int				ft_backup_stdin(int nb);
int				ft_backup_stdout(int nb);
int				ft_backup_stderr(int nb);
t_redir			*type_redir(char *str, int index, int len, int i);
void			ft_redirr_type8(t_redir *red);
int				ft_redirr_type1(t_redir *red);
int				ft_redirr_type2(t_redir *red);

/*
**check
*/

int				ft_check_cmd(t_shell *sh);
int				ft_check_redir(t_shell *sh);

/*
**pipe
*/

void			ft_pipe(t_cmd *cmd);
void			ft_pipe2(int pdes[2], t_cmd *cmd, int const readend, \
		int const writeemd);
void			ft_multi_pipe(t_cmd *cmd, int opt);
/*
**fill_cmd
*/

t_cmd			*ft_fill_cmd(char *line, int i, int j);

/*
** HEREDOC
*/

int				ft_fill_hash(char **av, char **env);
int				ft_hdoc(t_cmd *cmd);
char			*ft_ret_word_hdoc(char **word, int flag);
int				ft_signal_here(t_termc *tsh);
int				ft_line_hdoc(t_termc *t, char *word);
void			ft_display_prompt_hdoc(t_termc *tsh);
void			ft_reinit_hash(void);

/*
**FREE2.C
*/

void			free_shell(t_termc *tsh);
void			ft_free_free(t_termc *tsh);
void			ft_free_cmd(t_cmd *cmd);

#endif
