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
#include <dirent.h>
#include <sys/stat.h>

#define PATH_MAX 2048

/*****************************************************************************/
/*FROM DIRECTORY LINE_EDITION*/

typedef struct          s_term
{
    char                *dcstr;												//Del one caractere in screen
    char                *clrstr;											//Clean all screen and put cursor on the top left
    char                *cmstr;												//Move cursor %1 line , %1 col
    char                *cbstr;												//Clean begin line until end cursor
    char                *lestr;
	char                *lestru;												//Move cursor one caractere to left
	char 				*ristr;
    char                *ndstr;												//Move cursor one caractere to right
    char                *dlstr;												//Clean the line
    char                *dostr;
    char                *upstr;												//Up cursor one line
	char                *upstru;												//Up cursor one line
    char                *cdstr;												//Clean all screen until end
    char                *vistr;												//Cursor invisible
    char                *vestr;												//Cursor visible
	char                *cestr; /*STOP UNDERLINE*/
	char				bp[2048];
	char				area[2048];
    struct termios      old_termios;
    struct termios      term;
}                       t_term;

typedef struct          s_history
{
    int                 index;
    int                 new;
    int                 print;
    char                *data;
    struct  s_history   *next;
    struct  s_history   *prev;
}                       t_history;

typedef struct			hlist
{
    int                 ecrase_hist;
    char                *pwd;
	t_history			*begin;
    t_history           *current;
	t_history			*end;
}						hlist;

typedef struct          s_console
{
    size_t              total_line;
    size_t              char_pos;
}                       t_console;

typedef struct          s_lineterm
{
    char                c;
    int                 under;
    int                 s_pos;
    int                 index;
    struct s_lineterm   *next;
    struct s_lineterm   *prev;
}                       t_lineterm;

typedef	struct			tlist
{
    int                 lnk_before;
    int                 last;
	t_lineterm			*begin;
	t_lineterm			*end;
}						dlist;

typedef struct          s_key
{
    int                 backspace;
    int                 underline;
    int                 mleft;
    int                 mright;
    int                 cl;
	int                 k_tab;          //how time touch tab
}                       t_keyflag;

typedef struct          s_var_auto
{
    int                 row;
    int                 len;
    int                 ttl_jump;
    int                 down;
}                       t_var_auto;

typedef struct          s_autocompl
{
    char                *data;
    int                 index;
    struct s_autocompl  *next;
    struct s_autocompl  *prev;
}                       t_autocompl;

typedef struct          s_senti_auto
{
    char                *str;
    int                 finish;
	int					jump;
    int                 max_len;
    int                 row;
    int                 col;
    int                 pages;
    int                 more_pages;
    int                 nbr_word;
    int                 updaterow;
    int                 arrow;
    int                 clr_yes;
	int					can_print;
	int					possiblitie;
    t_autocompl         *begin;
    t_autocompl         *current;
    t_autocompl         *end;
}                       t_auto;

typedef struct          s_termc
{
	int					quotes;
    int                 auto_active;        //autocomple
    int                 multiauto_active;   //autocomple
	int					len_prompt;
	int 				repl;
	int 				sigint;
	char                *line_shell;
    t_auto              *autoc;
    dlist         		*line;
	dlist				*line_dup;
	hlist				*histmp;
    hlist               *histlist;
    t_term              *term;
    t_console           *console;
    t_keyflag           *keyflag;
}                       t_termc;

/*****************************************************************************/
/*FROM DIRECTORY GLOBBING*/
typedef struct		s_glob
{
	char			**s_tab;
	char			**res;
	char			*path;
	int				len;
}					t_glob;

/*******************************************/
/*              test de fusion              */

typedef struct		s_cmd
{
	char	        *line;
	char	        **av;
	int		        ac;
	int		        load;
    char	        **var;
    int             l_op;
    int             r_op;
    struct s_cmd    *next;
}					t_cmd;

typedef struct      s_shell
{
    char *line;
}                   t_shell;

typedef struct      s_redir
{
    int             in;
    int             out;
    int             type;
    int             close;
}                   t_redir;

void		ft_perror(char *str, int error, char *str2);

/******************************************************************************/
/********************************/
/*            replace           */
/********************************/

void 		ft_result_replace(t_shell *sh);
void		ft_replace(t_shell *sh);
void		ft_replace_dollar(t_shell *sh, int save);
void		ft_replace_tilde(t_shell *sh, int save);
char		*ft_replace_line(char *str1, char *value, char *str2);
char        *ft_add_escape(char *str);
/*********************************/
/*			REPLACE_HIST 		 */
/*********************************/
void 		ft_replace_exp_hist(t_termc *tsh);
void 		*ft_skip(t_lineterm *tmp, int len);
int 		ft_find3(t_termc *tsh, t_lineterm *begin, int *count);
int 		ft_find2(t_termc *tsh, t_lineterm *begin, int *count);
int 		ft_find(t_termc *tsh, t_lineterm *begin, int *count);
/*********************************/
/*			TOOL_REPLACE 		 */
/*********************************/
void 		ft_cpy_to_line(char *data, t_termc *tsh);
void 		ft_dupdlnk(dlist *line, dlist *tmp);
void 		ft_freedlnk(dlist *line);
void 		push_dupdlst(dlist *line, int c, int pos, int index);
int 		ft_word_here(t_lineterm *begin, char *word);
/*********************************/
/*			TOOL_REPLACE2 		 */
/*********************************/
void 		ft_join_all(char *word, char **line_tmp, int ret);
void 		ft_add_space(char **line, char *s_line, char *word);
/*********************************/
/*			REPLACE_GLOB 		 */
/*********************************/
void 		ft_replace_globbling_and_expansion(t_termc *tsh, t_lineterm *end);

/******************************************************************************/

/********************************/
/*            exec              */
/********************************/

void		ft_exec(char **av, char **env);
void		ft_exec_pipe(char **av, char **env);

/********************************/
/*            other             */
/********************************/

void		signal_sigint();
void		ft_display_env(char **env);
void		ft_chdir_error(char *path);
char		*ft_getenv(const char *name, char **env);
void		ft_fill_env(char **env);
char		**ft_replace_env(char **new_env, char **old_env);
char		*ft_remove_useless_path(char *str);
char		*ft_replace_str(char *new, char *old);
char		**ft_cp_env(char **env);
void		ft_charcat(char *str, char c);
void		free_tab_2d(char **tab);
int			tab_2d_len(char **tab);
char		**rapid_set(char *input, char **env, int j);
void		export_no_eq(t_cmd *cmd, int i);
void		export_with_eq(t_cmd *cmd, int i);
char		**load_env(char **env);
void		export_flagb(t_cmd *cmd);
void		replace_elem(char *compare, char *input, char **env);
int			check_correct_arg(t_cmd *cmd, int i);
void		export_flag_b(t_cmd *cmd, int i);
int			only_p(t_cmd *cmd);
int			check_pattern(char *str);
void		ft_display_export(char	**var);

int		    ft_skip_useless(char *line);
void		ft_cmd(t_cmd *cmd);
int		    ft_singleton(int nb, int opt);
int			ft_skip_quote(char *str);
int			ft_skip_dquote(char *str);
t_shell    	*ft_ret_sh(t_shell *arg);
char		**ft_var_var(char **arg);

/********************************/
/*         redirection          */
/********************************/

char        *ft_ret_word(char *line);
void        ft_fill_word(char *line, char *word);
int 		ft_redirection(t_cmd *cmd);
void		ft_remove_redirection();
int         ft_count_char_word(char *line);
int			ft_backup_stdin(int nb);
int			ft_backup_stdout(int nb);
int			ft_backup_stderr(int nb);
t_redir     *type_redir(char *str, int index);
void		ft_redirr_type8(t_redir *red);
void		ft_redirr_type1(t_redir *red);
void		ft_redirr_type2(t_redir *red);




char	**ft_var_env(char **arg);
char	*ft_var_pwd(char *arg);

t_cmd	*ft_fill_cmd(char *line, int i, int j);


#endif
