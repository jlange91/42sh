#ifndef SH21_H
# define SH21_H

# include <stdio.h>
# include <sys/wait.h>
# include <pwd.h>
# include <assert.h>
# include <termios.h>
# include <dirent.h>
# include "../libft/include/libft.h"
# include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
# include <fcntl.h>


#define PATH_MAX 2048

/*****************************************************************************/
/*FROM DIRECTORY LINE_EDITION*/

typedef struct          s_term
{
    char                *dcstr;												//Del one caractere in screen
    char                *clrstr;											//Clean all screen and put cursor on the top left
    char                *cmstr;												//Move cursor %1 line , %1 col
    char                *cbstr;												//Clean begin line until end cursor
    char                *lestr;												//Move cursor one caractere to left
    char                *ndstr;												//Move cursor one caractere to right
    char                *dlstr;												//Clean the line
    char                *dostr;												//Down cursor one line
    char                *upstr;												//Up cursor one line
    char                *cdstr;												//Clean all screen until end
    char                *vistr;												//Cursor invisible
    char                *vestr;												//Cursor visible
    char                *usstr;         /*START UNDERLNE*/
	char                *uestr; /*STOP UNDERLINE*/
	char                *cestr; /*STOP UNDERLINE*/
	char				bp[2048];
	char				area[2048];
    struct termios      old_termios;
    struct termios      term;
    int                 li;
    int                 co;
}                       t_term;

typedef struct          s_history
{
    char                *data;
    struct  s_history   *next;
    struct  s_history   *prev;
}                       t_history;

typedef struct			hlist
{
    int                 active;
    int                 error;
	int					up;
	int					down;
    int                 ecrase_hist;
    int                 line_history;
	t_history			*begin;
    t_history           *current;
	t_history			*end;
}						hlist;

typedef struct          s_console
{
    size_t              total_line;
    size_t              line_pos;
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
	size_t				lenght;
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
    int                 pos;
    int                 last;
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
    char                *line_shell;
	char				*pwd;
    int                 nbr_hist;
    int                 ret_signal;
    int                 move_cursor;
	int					quotes;
    int                 count_tab;          //how time touch tab
    int                 auto_active;        //autocomple
    int                 multiauto_active;   //autocomple
	int					len_prompt;
    t_auto              *autocompl;
    t_auto              *autocompl_binary;
    dlist         		*line;
	dlist				*line_dup;
	hlist				*history;
    hlist               *from_hist;
    t_term              *term;
    t_console           *console;
    t_keyflag           *keyflag;
}                       t_termc;

/*****************************************************************************/
/*FROM DIRECTORY GLOBBING*/
typedef struct          s_glob
{
    char                **tab_str;
    char                *line;
    char                *tmp;
	char				*before;
	char				*after;
	int					i;
	int					j;
	int					k;
	int					ret;
	char				**new_tab;
	char				**tmp_tab;
}                       t_glob;

/********************************************************************************/
/*FROM TREE DIRECTORY*/

typedef struct          s_cmd
{
    char                *str_type;
	char				*str_line;
    char                **str_t;
    int                 type;
}                       t_cmd;

/*******************************************/
/*              test de fusion              */

typedef struct      s_redir
{
    int             fd;
    int             close;
    struct s_redir  *next;
}                   t_redir;

typedef struct		s_shell
{
	char	*line;
	char	**av;
	int		ac;
	char	**env;
    char	*pwd;
    t_redir     *output;
    t_redir     *input;
    int         output_save;
    int         input_save;
}					t_shell;

void		ft_perror(char *str, int error, char *str2);

/********************************/
/*            replace           */
/********************************/

void		ft_replace(t_shell *sh);
void		ft_replace_dollar(t_shell *sh, int save);
void		ft_replace_tilde(t_shell *sh, int save);
char		*ft_replace_line(char *str1, char *value, char *str2);
char        *ft_add_escape(char *str);

/********************************/
/*            exec              */
/********************************/

void		ft_exec(char **av, char **env);

/********************************/
/*            other             */
/********************************/

void		signal_sigint();
void		ft_display_env(char **env);
void		ft_chdir_error(char *path);
char		*ft_getenv(const char *name, char **env);
void		ft_fill_env(t_shell *sh, char **env);
char		**ft_replace_env(char **new_env, char **old_env);
char		*ft_remove_useless_path(char *str);
char		*ft_replace_str(char *new, char *old);
char		**ft_cp_env(char **env);
void		ft_charcat(char *str, char c);
void		free_tab_2d(char **tab);
int			tab_2d_len(char **tab);
int         ft_skip_quote(char *str);
int         ft_skip_dquote(char *str);





int			ft_skip_useless(char *line);
int 		ft_redirection(t_shell *sh);
void		ft_remove_redirection(t_shell *sh);





/********************************/
/*            ret_word          */
/********************************/

char    *ft_ret_word(char *line, int *size);
void     ft_fill_word(char *line, char *word);

int     ft_count_char_word(char *line, int *nb);


void			ft_cmd(t_shell *sh);
int		    ft_singleton(int nb, int opt);

#endif
