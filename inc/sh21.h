#ifndef SH21_H
# define SH21_H

# include <stdio.h>
# include <sys/wait.h>
# include <pwd.h>
# include <assert.h>
# include <termios.h>
# include <dirent.h>
# include "../libft/include/libft.h"
#include <dirent.h>
#include <sys/stat.h>

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
    t_autocompl         *begin;
    t_autocompl         *current;
    t_autocompl         *end;
}                       t_auto;

typedef struct          s_shell
{
    char                *line_shell;
    int                 nbr_hist;
    int                 ret_signal;
    int                 move_cursor;
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
}                       t_shell;

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

/*****************************************************************************/
/*FROM DIRECTORY ENV_TERM*/

typedef struct      s_env
{
    char            *line_str;
    char            **av;
    char            *line_env;
    char            *getenv_path;
    int             index;
    struct s_env    *next;

}                   t_env;

/*******************************************************************************/
/*FROM DIRECTORY TOKEN*/

typedef enum            s_tk
{
    TOKEN_DR_R,
    TOKEN_R_R,
    TOKEN_DR_L,
    TOKEN_R_L,
    TOKEN_BACK_R_R,
    TOKEN_QUOTE,
    TOKEN_R_R_BACK,
    TOKEN_MULTI_SEM,
    TOKEN_OR,
    TOKEN_PIPE,
    TOKEN_AND,
    TOKEN_BACKGROUND,
    TOKEN_CMD,
    TOKEN_EOL
}                       e_token;

typedef struct          s_token
{
    char                *cmd;
    int                 type;
    int                 cmd_len;
    int                 pos;
    struct s_token      *next;
    struct s_token      *prev;
}                       t_token;

typedef struct          t_token
{
    const char          *tab_token[14];
    const char          *basic_token[6];
    int                 type;
    t_token             *begin;
    t_token             *end;
}                       dtoken;

typedef struct          s_lexer
{
    char                *str;
    dtoken              *token;
}                       t_lexer;

/********************************************************************************/
/*FROM TREE DIRECTORY*/

typedef struct          s_cmd
{
    char                *str_type;
	char				*str_line;
    char                **str_t;
    int                 type;
}                       t_cmd;

typedef struct          s_tree
{
    int                 type;
    char                *str;
    struct s_tree       *left;
    struct s_tree       *right;
}                       t_tree;

#endif
