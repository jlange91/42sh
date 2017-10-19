#ifndef LINE_EDITION_H
# define LINE_EDITION_H

# include "sh21.h"
# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>
# include <time.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

/*  KEYCODE*/

# define UP_AUTO    'A'
# define DOWN_AUTO  'B'
# define LEFT_AUTO  'D'
# define RIGTH_AUTO 'C'

# define	UP			4283163
# define	LEFT		4479771
# define	RIGHT		4414235
# define	DOWN		4348699 
# define	SPACE		32
# define	BACKSPACE	127
# define  	OPT_UP		1096489755	
# define  	OPT_DOWN	1113266971	
# define  	HOME		4741915	
# define  	END			4610843	
# define  	OPT_F		1146821403	
# define  	OPT_B		1130044187	
# define  	CW			23
# define  	CL			12
# define  	OPT_C		42947	
# define  	OPT_X		8948194	
# define  	OPT_P		32975	
# define    TAB         9
# define  	MAJ_RIGHT	73883020516123
# define  	MAJ_LEFT	74982532143899 

/*COLORS PROMPT*/

# define RED		"\x1B[31m"
# define RESET		"\033[0m"
# define BLUE		"\x1B[34m"
# define YELLOW		"\033[33m"
# define PINK		"\x1B[38;5;9m"
# define ORANGE_FRONT "\033[38;5;20m"
# define PURPLE_BACK "\033[48;5;9m"
# define GREEN_FRONT "\033[38;5;33m"

typedef void(*t_k) (t_lineterm *end, t_shell *shell, t_env *env);

/**************************************/
/*DEBUG*/
/*#define free(aa) {printf("[%s][ligne %d] Liberation bloc %s a %p\n",__FILE__,__LINE__,#aa,aa);free(aa);}*/

/**************************************************************************************/

t_shell             *init_shell(t_env *env);

/**************************************************************************************/
/*TERM*/
void				ft_init_console(t_shell *shell, dlist *line);
void                ft_end_term(t_shell *shell);
int					ft_insert_lnk_void(dlist *line);

/***************************************************************************************/
/*HISTORY*/
void				ft_history(t_shell *shell, int c);
int                 ft_count_history(void);
int                 ft_fill_history(t_shell *shell);
int                 ft_init_fill_history(hlist *from_hist);
int                 ft_find_history(t_shell *shell);

/***************************************************************************************/
/*HISTORY2*/
void				ft_add_tmp_history(t_shell *shell, const char *str);
void                ft_free_history(hlist *history);
int                 ft_add_file_history(t_shell *shell);
int                 ft_add_file_history_no_flag(t_shell *shell);

/***************************************************************************************/
/*READLINE*/
char				*ft_line_input(t_shell *shell, t_env *env);

/***************************************************************************************/
/*UTILS_READ*/
int                 ft_reset_line(t_shell *shell, int ret);

/**************************************************************************************/
/*TOOL READLINE*/
void                ft_fill_back_dlst(dlist *line, int c, int i);
void				ft_fill_back_hlst(hlist *line, const char *str);
void                ft_insert_dlnk(t_lineterm *end, t_shell *shell, int c, int i);
int		            ft_count_dlnk(t_shell *shell);

/**************************************************************************************/
/*TOOL READLINE2*/
int					ft_display_char(t_lineterm *begin, t_shell *shell);
int                 ft_display(t_shell *shell, int *nbr, int close);

/***************************************************************************************/
/*PROMPT*/
void                ft_display_prompt(t_shell *shell);

/***************************************************************************************/
/*DISPLAY*/
void				ft_display_dlnk(dlist *line, t_lineterm *current, t_shell *shell);

/***************************************************************************************/
/*KEY*/
int					ft_is_key(dlist *line, t_shell *sehll, long c, t_env *env);

/**************************************************************************************/
/*FT_KEY2*/
int                 ft_other_key(t_lineterm *end, t_shell *shell, long c, t_env *env);

/*****************************************************************************************/
/*MOVE_SELECTION*/
void                ft_move_right(t_lineterm *end, t_shell *shell, t_env *env);
void                ft_move_left(t_lineterm *end, t_shell *shell, t_env *env);
void                ft_move_mright(t_lineterm *end, t_shell *shell, t_env *env);
void                ft_move_mleft(t_lineterm *end, t_shell *shell, t_env *env);

/*****************************************************************************************/
/*MOVE_WORD*/
void                ft_move_begin(t_lineterm *end, t_shell *shell, t_env *env);
void                ft_move_end(t_lineterm *end, t_shell *shell, t_env *env);
void                ft_move_word_forward(t_lineterm *end, t_shell *shell, t_env *env);
void                ft_move_word_back(t_lineterm *end, t_shell *shell, t_env *env);

/*****************************************************************************************/
/*CPY_CUT_DUP*/
void				ft_dup_line(t_lineterm *end, t_shell *shell, t_env *env);
void				ft_past_line(t_lineterm *end, t_shell *shell, t_env *env);
void				ft_cut_line(t_lineterm *end, t_shell *shell, t_env *env);

/*****************************************************************************************/
/*MOVE_UP_DOWN*/
void                ft_move_up_line(t_lineterm *end, t_shell *shell, t_env *env);
void                ft_move_down_line(t_lineterm *end, t_shell *shell, t_env *env);
void           		ft_move_history(t_shell *shell, t_history **current, int flag);

/*****************************************************************************************/
/*TOOL*/
void                ft_free_autocompletion(t_auto **autocompl);
void                ft_free_all(t_shell *all);
void				ft_free_dlist(dlist **line);
t_lineterm			*ft_dont_get_prompt(t_lineterm *tmp);
int                 ft_inputstr(int c);
size_t              get_columns();

/**************************************************************************************/
/*SIGNAL*/
void				ft_handle_signal(int signum);
void                ft_handle_signal2(int signum);
void				ft_catch_sigwinch(int signum);

/**************************************************************************************/
/*FT_LINE_EDITION*/
int                 ft_line_edition(t_env *env_c, t_shell *shelli, t_lexer *lexer);


char **ft_fill_av(char *line);

#endif
