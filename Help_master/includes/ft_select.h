/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebrito <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 14:12:39 by adebrito          #+#    #+#             */
/*   Updated: 2017/12/19 12:38:19 by adebrito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <../../libft/include/libft.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <termcap.h>
# include <term.h>
# include <signal.h>
# include <sys/stat.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>

# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define RESET "\x1B[0m"

typedef struct			s_elem
{
	char	*str;
	int		select;
}						t_elem;

typedef struct			s_select
{
	struct termios		default_term;
	t_elem				*elem;
	char				**env;
	int					height;
	int					width;
	int					nb_elem;
	int					cursor_line;
	int					max_strlen;
}						t_select;

int						ft_signal();
t_select				*keep_term(t_select *select);
void					ft_init_term(t_select **select);
int						ft_putc(int c);
int						ft_find_window_len(t_select **select);
void					ft_print_all(t_select **select, int i, int col);
void					ft_modify_elem(t_select **select, int i, int j);
void					ft_escape(t_select **select, char **content);
void					ft_valide_select(t_select **select);
void					ft_putab_inline(char **content);
void					ft_read_commande(t_select **select);
void					ft_arrow_key(t_select **select, char *buf);
void					ft_select(t_select **select);
void					color(mode_t mode);
#endif
