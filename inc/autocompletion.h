#ifndef AUTOCOMPLETION_H
# define AUTOCOMPLETION_H

# include "sh21.h"
# include "line_edition.h"
# include "env_term.h"

#define   RD_EOF   -1
#define   RD_EIO   -2

/**************************************************************************************/
/*FT_AUTO_COMPLETION*/

void                ft_autocompletion(t_lineterm *end, t_shell *shell, t_env *env);
char				*ft_to_str(t_shell *shell);
int                 curs();

/**************************************************************************************/
/*FT_PRINT_AUTO_COMPLETION*/
void                ft_menu_autocompletion(t_auto *select, t_shell *shell, int *total); 
int                 ft_diff_print(t_auto *select, t_autocompl *begin, int nbr, int flag);

/**************************************************************************************/
/*FT_AUTO_COMPLETION_KEY*/

void                ft_auto_up(t_lineterm *end, t_shell *shell);
void                ft_auto_down(t_lineterm *end, t_shell *shell);
void                ft_autoright(t_lineterm *end, t_shell *shell);
void                ft_autoleft(t_lineterm *end, t_shell *shell);
void                ft_select(t_lineterm *end, t_shell *shell);

/**************************************************************************************/
/*TOOL_PRINT_AUTOCOMPLETION*/
void                ft_display_autocompletion(t_shell *shell, int *down);
int                ft_init_value(t_shell *shell, t_auto *select);
int                 ft_max_len(t_auto *select);
int                 ft_count(t_auto *select);
int                 ft_cursor_update(void);


/**************************************************************************************/
/*FT_INIT_AUTOCOMPLETION*/
void                ft_init_simple_autocompl(t_shell *shell, t_env *env);
int					ft_init_autocompl(t_shell *shell, char *line, t_env *env);

/**************************************************************************************/
/*FT_INIT_AUTOCOMPLETION2*/
void                ft_init_autocompl_binary(t_shell *shell);

/**************************************************************************************/
/*TOOL_AUTOCOMPLETION*/
void                ft_fill_back_autocompl(t_auto *autocompl, char *file, int index);
char                *ft_to_str(t_shell *shell);
char                *ft_before_antislash(char *str, int ret); 
char                *ft_after_antislash(char *str, int *ret);

/**************************************************************************************/
/*TOOL2_AUTOCOMPLETION*/
void                ft_check_is_dir(t_shell *shell);
void                ft_cpy_autocompl_to_lineshell(t_shell *shell);
void                ft_put_antislash_one_word(t_shell *shell);
char                *ft_antislash_here_bis(int limit, int len, char *str);
int                 ft_reset(t_shell *shell, t_env *env);

/**************************************************************************************/
/*MULTI_CHOICE_AUTOCOMPLETION*/
int                 ft_fill_same_word(t_shell *shell, t_env *env);

/**************************************************************************************/
/*UPDATE_CURSOR*/
int                 ft_cursor_position(const int tty, int *const rowptr);
int                 ft_current_tty(void);

/**************************************************************************************/
/*MULTI_PAGES_AUTOCOMPLETION*/

void                ft_multi_pages(t_auto *select, t_shell *shell, t_autocompl *begin, int *total);
#endif
