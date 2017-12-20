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

static void ft_cpy(char *line, t_termc *tsh, int count, int index)
{
	int i;

	i = 0;
	tsh->autoc->updaterow = 0;
	while (line[i])
	{
		push_backdlst(tsh->line, line[i], 1);
		i++;
	}
	if (index < count)
		push_backdlst(tsh->line, ' ', 1);
}

static char	**ft_reset_glob(t_termc *tsh, char *line)
{
	char		**tmp_tab;

	ft_clean_line(tsh);
	tmp_tab = ft_strsplit2(line);
	return (tmp_tab);
}

t_cmd		*ft_ret_cmd(t_cmd *arg)
{
	static t_cmd *cmd = NULL;

	if (arg)
		cmd = arg;
	return (cmd);
}

void		ft_replace_all(char *line, t_termc *tsh)
{
	int			i;
	int 		count;
	char		**tabt;
	char		*tmp;
	t_cmd		 	*cmd;

	cmd = ft_ret_cmd(NULL);
	tabt = ft_reset_glob(tsh, line);
	i = -1;
	count = ft_count_dtab(tabt) - 1;
	while (tabt[++i])
	{
		if (ft_glob_here(tabt[i]) && (tmp = ft_glob(tabt[i])) != NULL)
		{
			tsh->key_tab = 0;
			ft_cpy(tmp, tsh, count, i);
			free(tmp);
		}
		else
		{
			cmd->line = ft_strdup(tabt[i]);
			ft_replace(cmd);
			(ft_strlen(cmd->line) > 0) ? ft_cpy(cmd->line, tsh, count, i) :
			ft_cpy(tabt[i], tsh, count, i);
			free(cmd->line);
		}
	}
	ft_free_tab(tabt);
}
