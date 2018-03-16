/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 17:11:29 by vmartins          #+#    #+#             */
/*   Updated: 2018/01/30 16:20:31 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOCOMPLETION_H
# define AUTOCOMPLETION_H

# include "sh21.h"
# include "line_edition.h"

# define RD_EOF -1
# define RD_EIO -2

/*
**FT_AUTO_COMPLETION.C
*/

void		ft_autocompletion(t_lineterm *end, t_termc *shell);

/*
**FT_PRINT_AUTO_COMPLETION.C
*/

void		ft_menu_autocompletion(t_auto *select, t_termc *shell);
void		ft_diff_print(t_auto *sel, t_autocompl *begin, int nbr, int flag);

/*
**FT_AUTO_COMPLETION_KEY
*/

void		ft_auto_down_up(t_lineterm *end, t_termc *shell, int direction);
void		ft_select(t_lineterm *end, t_termc *shell);
void		ft_automove(t_lineterm *end, t_termc *shell, int flag);

/*
**TOOL_PRINT_AUTOCOMPLETION.C
*/

void		ft_display_autocompletion(t_termc *shell);
int			ft_init_value(t_termc *shell, t_auto *select);
int			ft_max_len(t_auto *select);
int			ft_cursor_update(void);
int			ft_getcursor(int i, int res, t_termc *tsh);

/*
**FT_INIT_AUTOCOMPLETION.C
*/

int			ft_init_autocompl(t_termc *shell, char *line);

/*
**FT_INIT2_AUTOCOMPLETION2.C
*/

void		ft_init_simple_autocompl(t_termc *shell, int dot, char *line);
int			ft_check_open(char *line);

/*
**TOOL_AUTOCOMPLETION.C
*/

void		ft_fill_back_autocompl(t_auto *autocompl, char *file, int index);
char		*ft_after_antislash(char *str, int *ret);
int			ft_count(t_auto *select);
int			ft_not_str(char *str, t_termc *tsh);

/*
**TOOL2_AUTOCOMPLETION.C
*/

void		ft_check_is_dir(t_termc *shell);
void		ft_cpy_autocompl_to_lineshell(t_termc *shell);
int			ft_reset(t_termc *shell);
int			ft_dir_or_not(char *file);

/*
**MULTI_CHOICE_AUTOCOMPLETION.C
*/

int			ft_fill_same_word(t_termc *shell);

/*
**UPDATE_CURSOR.C
*/

int			ft_cursor_position(const int tty, int *const rowptr);
int			ft_current_tty(void);

/*
**MULTI_PAGES.C
*/

void		ft_mpages(t_auto *a, t_termc *t, t_autocompl *aut);
int			ft_clean_all_letter(int i, int res);

/*
**PRINT.C
*/

t_var_auto	*ft_init_var_auto(t_auto *select);
void		ft_display_autocompl(t_autocompl *begin, t_auto *select);

#endif
