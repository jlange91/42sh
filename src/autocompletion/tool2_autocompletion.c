#include "../../inc/autocompletion.h"

/*
 * * FUNCTION ADD "/" to tsh_line
 * if line from tsh_line is dir
 *
 * We split the line for get last word and check if is dir;
 */
void    ft_check_is_dir(t_termc *tsh)
{
	int         i;
	char        **tab_word;
	char        *tmp;
	struct stat info;

	tmp = ft_to_str(tsh, 0);
	tab_word = ft_strsplit2(tmp);
	free(tmp);
	i = ft_count_dtab(tab_word) - 1;
	ft_memset(&info, 0, sizeof(struct stat));
	stat(tab_word[i], &info);
	if (S_ISDIR(info.st_mode) && tsh->line->end->c != '/'
			&& tsh->line->end->c != ' ' && tsh->line->end->c != '.')
		push_backdlst(tsh->line, '/', 0 + 2);
	ft_free_tab(tab_word);
}

void    ft_cpy_autocompl_to_lineshell(t_termc *tsh)
{
	int i;
	int j;

	i = -1;
	j = 0;
	if (tsh->autoc->str != NULL)
	{
		j = ft_strlen(tsh->autoc->str) - 1;
		while (tsh->autoc->str[j] != '/' && tsh->autoc->str[j] != ' ')                             //REMOVE LAST LETTER AFTER / FOR REPLACE
			j--;
		j++;
		while (tsh->autoc->str[++i] && i < j)
			push_backdlst(tsh->line, tsh->autoc->str[i], i + 2);
	}
	ft_check_is_dir(tsh);
	i = -1;
	while (tsh->autoc->current->data[++i])
		push_backdlst(tsh->line, tsh->autoc->current->data[i], i + 2);
}

int    ft_reset(t_termc *tsh)
{
	tputs(tsh->term->cdstr, 1, ft_inputstr);
	if (tsh->autoc->str != NULL)
	{
		free(tsh->autoc->str);
		tsh->autoc->str = NULL;
	}
	tsh->auto_active = 1;
	tsh->line->last = 1;
	if (tsh->autoc->finish == 1)
		tsh->autoc->finish = 0;
	if (ft_count_dlnk(tsh, 0) == 0)
	{
		ft_init_simple_autocompl(tsh);
		return (1);
	}
	return (0);
}

int		ft_dir_or_not(char *line)
{
	struct stat info;

	ft_memset(&info, 0, sizeof(info));
	stat(line, &info);
	if (S_ISDIR(info.st_mode))
		return (1);
	return (0);
}
