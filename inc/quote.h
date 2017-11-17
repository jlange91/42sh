#ifndef QUOTE_H
# define QUOTE_H

# include "sh21.h"

# define Q_LEFT 'D'
# define Q_RIGHT 'C'

/********************************/
/*            quote             */
/********************************/

char 		**ft_fill_av(char *line);
void     	ft_fill(char *line, char **av);
int     	ft_count_av1(char *line);
int     	ft_count_av2(char *line, char **av);
int     	ft_char_escape(char c);
int			ft_check_quote(char *line);
int			ft_return(char c);
int			ft_skip_useless(char *line);
void		ft_fill_line(t_termc *shell, char **env);

#endif