/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 16:29:52 by vmartins          #+#    #+#             */
/*   Updated: 2018/01/25 13:03:23 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDITION_H
# define LINE_EDITION_H

# include "sh21.h"
# include <sys/ioctl.h>
# include <term.h>
# include <time.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

/*
**KEYCODE
*/

# define UP			4283163
# define LEFT		4479771
# define RIGHT		4414235
# define DOWN		4348699
# define SPACE		32
# define BACKSPACE	127
# define OPT_UP		1096489755
# define OPT_DOWN	1113266971
# define NO_PRINT	-4
# define HOME		4741915
# define END		4610843
# define OPT_F		1146821403
# define OPT_B		1130044187
# define CL			12
# define OPT_C		42947
# define OPT_X		8948194
# define OPT_V		10127586
# define OPT_P		32975
# define TAB		9
# define MAJ_RIGHT	73883020516123
# define MAJ_LEFT	74982532143899
# define EOT 		4

/*
**COLORS PROMPT
*/

# define RED			"\x1B[31m"
# define RESET			"\033[0m"
# define BLUE			"\x1B[36m"
# define YELLOW			"\033[33m"
# define PINK			"\x1B[38;5;9m"
# define ORANGE_FRONT	"\033[38;5;20m"
# define PURPLE_BACK	"\033[48;5;9m"
# define GREEN_FRONT	"\033[38;5;33m"
# define GREEN			"\x1B[32m"

/*
**HISTORY
*/

# define NAME_HIST		"/.42sh_history"
# define REPLACE		1
# define CTR_L			2

typedef void(*t_k) (t_lineterm *end, t_termc *shell);

/*
**INIT
*/

t_termc		*init_termc(char **env);
void		ft_init_signal(void);

/*
**INIT2
*/

void		ft_init_termc2(t_termc **tsh);

/*
**INIT3
*/

void		ft_init_termc3(t_termc *tsh);
t_console	*init_console(void);

/*
**TERM
*/

void		ft_init_console(t_termc *shell, t_dlst *line);
void		ft_end_term(t_termc *shell);
int			ft_insert_lnk_void(t_dlst *line);
int			ft_init_terminal_mode(t_termc *shell);
int			ft_fill_prompt(t_dlst *line);

/*
**HISTORY
*/

void		ft_history(t_termc *shell, int c);
int			ft_count_history(char *path);
int			ft_fill_history(t_termc *shell);
int			ft_init_fill_history(t_hist *histlist);
int			ft_find_history(t_termc *shell);

/*
**HISTORY2
*/

void		ft_add_tmp_history(t_termc *shell, const char *str);
void		ft_free_history(t_hist *history);
int			ft_add_file_history(t_termc *shell);
int			ft_add_file_history_no_flag(t_termc *shell);

/*
**READLINE
*/

char		*ft_readline(t_termc *shell);
int			ft_what_arrow(long *c, int *stp, char k);

/*
**UTILS_READ
*/

int			ft_reset_line(t_termc *shell);
int			ft_save_line(t_termc *tsh);
int			ft_inputstr(int c);
size_t		get_columns();
char		*ft_to_str(t_termc *tsh, int flag);

/*
**TOOL READLINE
*/

void		push_backdlst(t_dlst *line, int c, int i);
void		push_backhist(t_hist *line, const char *str, int index, int i);
void		ft_insert_dlnk(t_lineterm *end, t_termc *shell, int c, int i);
int			ft_count_dlnk(t_termc *shell, int flag);
t_lineterm	*find_cursor(t_lineterm *end, int flag);

/*
**TOOL READLINE2
*/

int			ft_display_char(t_lineterm *begin, t_termc *shell);
void		ft_display(t_termc *shell);

/*
**PROMPT
*/

void		ft_display_prompt(t_termc *shell);

/*
**TOOLS_DISPLAY
*/

int			ft_ret_ligne(t_lineterm *end, t_termc *tsh);

/*
**DISPLAY
*/

void		ft_display_dlnk(t_dlst *line, t_lineterm *current, t_termc *shell);

/*
**KEY
*/

int			ft_what_key(long *c, int *stp, char k);

/*
**ACTION_KEY
*/

int			ft_action_key(t_dlst *line, t_termc *sehll, long c);
void		ft_ctr_d(t_termc *tsh);

/*
**ACTION_KEY2
*/

int			ft_other_key(t_lineterm *end, t_termc *shell, long c);

/*
**MOVE_SELECTION
*/

void		ft_move_right(t_lineterm *end, t_termc *shell);
void		ft_move_left(t_lineterm *end, t_termc *shell);
void		ft_move_mright(t_lineterm *end, t_termc *shell);
void		ft_move_mleft(t_lineterm *end, t_termc *shell);

/*
**MOVE_WORD
*/

void		ft_move_begin(t_lineterm *end, t_termc *shell);
void		ft_move_end(t_lineterm *end, t_termc *shell);
void		ft_move_word_forward(t_lineterm *end, t_termc *shell);
void		ft_move_word_back(t_lineterm *end, t_termc *shell);

/*
**CPY_CUT_DUP
*/

void		ft_dup_line(t_lineterm *end, t_termc *shell);
void		ft_past_line(t_lineterm *end, t_termc *shell);
void		ft_cut_line(t_lineterm *end, t_termc *shell);

/*
**MOVE_UP_DOWN2
*/

void		ft_move_down_line_auto(t_lineterm *end, t_termc *tsh);

/*
**MOVE_UP_DOWN
*/

void		ft_move_up_line(t_lineterm *end, t_termc *shell);
void		ft_move_down_line(t_lineterm *end, t_termc *shell);
void		ft_move_history(t_termc *shell, t_history **current, int flag);

/*
**TOOL
*/

void		ft_clean_line(t_termc *tsh);
t_lineterm	*ft_ps1(t_lineterm *tmp);

/*
**FREE
*/

void		ft_free_autocompletion(t_auto **autocompl);
void		ft_free_all(t_termc *all);
void		ft_free_t_dlst(t_dlst **line);

/*
**SIGNAL
*/

void		ft_handle_signal(int signum);

#endif
