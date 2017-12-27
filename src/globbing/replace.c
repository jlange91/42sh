#include "../../inc/globbing.h"
#include "../../inc/sh21.h"
#include "../../inc/line_edition.h"

void	ft_init_escape_tab(char *escape_tab)
{
	escape_tab[0] = '!';
	escape_tab[1] = '"';
	escape_tab[2] = '$';
	escape_tab[3] = '&';
	escape_tab[4] = '\'';
	escape_tab[5] = '(';
	escape_tab[6] = ')';
	escape_tab[7] = '*';
	escape_tab[8] = ',';
	escape_tab[9] = ':';
	escape_tab[10] = ';';
	escape_tab[11] = '<';
	escape_tab[12] = '=';
	escape_tab[13] = '>';
	escape_tab[14] = '?';
	escape_tab[15] = '@';
	escape_tab[16] = '[';
	escape_tab[17] = '\\';
	escape_tab[18] = ']';
	escape_tab[19] = '^';
	escape_tab[20] = '`';
	escape_tab[21] = '{';
	escape_tab[22] = '|';
	escape_tab[23] = '}';
	escape_tab[24] = '\0';
}

void ft_cpy(char *line, t_termc *tsh)
{
	int i;

	i = 0;
	tsh->autoc->updaterow = 0;
	while (line[i])
	{
		push_backdlst(tsh->line, line[i], 1);
		i++;
	}
}

static inline void ft_get_result(char *after, t_termc *tsh, t_shell *sh)
{
	char 		*glob;

	if (ft_glob_here(after) && (glob = ft_glob(after)) != NULL)
	{
		tsh->key_tab = 0;
		ft_cpy(glob, tsh);
		free(glob);
		tsh->repl = 1;
	}
	else
	{
		sh->line = ft_strdup(after);
		ft_replace(sh);
		if (ft_strcmp(sh->line, after) != 0 && ft_strlen(sh->line) > 0)
		{
			ft_cpy(sh->line, tsh);
			tsh->repl = 1;
		}
		else
			ft_cpy(after, tsh);
		free(sh->line);
	}
	ft_strdel(&after);
}

int 		ft_replace_all(char *line, t_termc *tsh)
{
	int 		i;
	char 		*after;
	char 		*before;
	t_shell 	*sh;

	ft_clean_line(tsh);
	sh = ft_ret_sh(NULL);
	i = ft_strlen(line);
	while (--i > 0)
		if (line[i] == ' ')
			break;
	after = ft_strtrim2(&line[i], ' ', '\t');
	before = ft_strndup(line, i + 1);
	if (ft_strlen(before) == 1)
		before[0] = '\0';
	ft_cpy(before, tsh);
	ft_strdel(&before);
	ft_get_result(after, tsh, sh);
	return (0);
}
