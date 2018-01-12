#include "../../inc/quote.h"
#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"

void	ft_fill_line(t_termc *tsh)
{
	char 	*tmp;
	char 	*line;

	line = ft_readline(tsh);
	if (tsh->quotes)
	{
		tmp = NULL;
		tsh->quotes = 0;
		free(line);
		tsh->line_shell = ft_strdup(ft_skel_quote(&tmp, 0));
		tsh->line_shell[ft_strlen(tsh->line_shell) - 1] = '\0';
		ft_skel_quote(&tmp, 1);
	}
	else
	{
		tsh->line_shell = ft_strdup(line);
		free(line);
	}
	ft_end_term(tsh);
}
