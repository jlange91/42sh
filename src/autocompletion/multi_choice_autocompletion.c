#include "../../inc/autocompletion.h"

static void 	ft_suitlist(t_termc *tsh, char *after, t_auto *tmp, int i)
{
	int test;
	t_autocompl *begin;
	t_autocompl *begin_tmp;

	begin = tsh->auto_binary->begin;
	while (begin)
	{
		if (ft_strncmp(after, begin->data, ft_strlen(after)) == 0)
		{
			test = 0;
			begin_tmp = tmp->begin;
			while (begin_tmp)
			{
				if (ft_strcmp(begin_tmp->data, begin->data) == 0)
				{
					test = 1;
					break;
				}
				begin_tmp = begin_tmp->next;
			}
			if (!test)
				ft_fill_back_autocompl(tmp, begin->data, ++i);
		}
		begin = begin->next;
	}
}

static t_auto  *ft_sort_list(t_termc *tsh, char *after, int ret)
{
	int         i;
	t_auto      *tmp;
	t_autocompl *begin;

	if ((tmp = (t_auto *)malloc(sizeof(*tmp))) == NULL)
		return (NULL);
	tmp->begin = NULL;
	tmp->end = NULL;
	tmp->current = NULL;
	begin = tsh->autoc->begin;
	i = 0;
	if (begin)																					//CURRENT DIRECTORY
	{
		while (begin)
		{
			if (ft_strncmp(after, begin->data, ft_strlen(after)) == 0)
				ft_fill_back_autocompl(tmp, begin->data, ++i);
			begin = begin->next;
		}
        if (ret)																				//IF MULTIAUTO_ACTIVE :)
			ft_suitlist(tsh, after, tmp, i);
	}
	return (tmp);
}

static int  ft_try_fill(t_termc *tsh, char *after, int *flag, int ret)
{
	int         i;
	t_auto      *tmp;

	tmp = NULL;
	if ((tmp = ft_sort_list(tsh, after, ret)) != NULL)
	{
		ft_free_autocompletion(&tsh->autoc);
		i = 0;
		*flag = (ft_count(tmp) < 1) ? 0 : 1;
		while (tmp->begin)
		{
			ft_fill_back_autocompl(tsh->autoc, tmp->begin->data, i++);
			tmp->begin = tmp->begin->next;
		}
		tsh->autoc->current = tsh->autoc->begin;
		ft_free_autocompletion(&tmp);
		free(tmp);
	}
	return (0);
}

int    ft_fill_same_word(t_termc *tsh)
{
	char        *after;
	char        *tmp_line;
	int         ret;
	int         flag;

	ret = 0;
	flag = 0;
	if (tsh->autoc->str != NULL && tsh->autoc->begin != NULL)
	{
		tmp_line = (ft_dir_or_not(tsh->autoc->str)) ?
		ft_strjoin(tsh->autoc->str, "/") : ft_strdup(tsh->autoc->str);
		if ((after = ft_after_antislash(tmp_line, &ret)) != NULL)
		{
			ft_try_fill(tsh, after, &flag, 0);
			free(after);
		}
		else
		{
            (tsh->multiauto_active == 1) ? ft_try_fill(tsh, tmp_line, &flag, 0)
			: ft_try_fill(tsh, tmp_line, &flag, 1);
			ft_init_autocompl(tsh, tmp_line);
		}
		free(tmp_line);
	}
	return (flag);
}
