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

static void ft_cpy(char *line, t_termc *tsh, int ret)
{
	int i;

	i = 0;
	while (line[i])
	{
		ft_fill_back_dlst(tsh->line, line[i], 1);
		i++;
	}
	(void)ret;
}

static char	**ft_reset_glob(t_termc *tsh, char *line)
{
	char		**tmp_tab;

	ft_clean_line(tsh);
	tmp_tab = ft_strsplit2(line);
	return (tmp_tab);
}

void		ft_replace_all(char *line, t_termc *tsh)
{
	int			i;
	char		**tmp_tab;
	char		*tmp;
	// t_shell		sh;

	tmp_tab = ft_reset_glob(tsh, line);
	i = 0;
	while (tmp_tab[i])
	{
		if (ft_glob_here(tmp_tab[i]))
		{
			tmp = ft_glob(tmp_tab[i]);
			ft_cpy(tmp, tsh, 0);
			free(tmp);
		}
		else
		{
			// sh.line = ft_strdup(tmp_tab[i]);
			// ft_replace(&sh);
			if (i != ft_count_dtab(tmp_tab) - 1)
				tmp_tab[i] = ft_free_join(tmp_tab[i], " ", 'L');
			ft_cpy(tmp_tab[i], tsh, 1);
			// free(sh.line);
		}
		i++;
	}
	ft_free_tab(tmp_tab);
}
