#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"
#include "../../inc/globbing.h"
#include "../../inc/sh21.h"

static inline void *ft_result(t_termc *tsh, dlist *tmp, int flag, int i)
{
	t_lineterm *begin;

	begin = ft_skip(tmp->begin, i);
	if (flag == 1 && begin && ft_isdigit(begin->c) && ft_find(tsh, begin, &i))
	{
		tmp->begin = ft_skip(tmp->begin, i);
		return ((dlist *)tmp);
	}
	else if (flag == 2 && ft_find2(tsh, begin, &i))
	{
		tmp->begin = ft_skip(tmp->begin, i);
		return ((dlist *)tmp);
	}
	else if (flag == 3 && ft_find3(tsh, begin, &i))
	{
		tmp->begin = ft_skip(tmp->begin, i);
		return ((dlist *)tmp);
	}
	return (NULL);
}

static inline int ft_replace_pattern(dlist *tmp, t_termc *tsh)
{
	if (tmp->begin->c == '\\' || !tmp->begin->next || tmp->begin->c != '!')
		return (0);
	if (tmp->begin->next->c != '\\' && tmp->begin->next->c == '!')
	{
		tmp->begin = ft_skip(tmp->begin, 2);
		ft_cpy_to_line(tsh->histlist->end->data, tsh);
		return (1);
	}
	else if (tmp->begin->next->c != '\\' && tmp->begin->next->c == '-')
	{
		if ((tmp = ft_result(tsh, tmp, 1, 2)) != NULL)
			return (1);
	}
	else if (ft_isdigit(tmp->begin->next->c) || ft_isalpha(tmp->begin->next->c)\
 		|| tmp->begin->next->c == '\\')
	{
			if ((tmp = ft_result(tsh, tmp, 2, 1)) != NULL)
				return (1);
	}
	else if (tmp->begin->next->c == '?')
	{
		if ((tmp = ft_result(tsh, tmp, 3, 2)) != NULL)
			return (1);
	}
	return (0);
}

void 		*ft_skip(t_lineterm *tmp, int len)
{
	int i;

	if (tmp != NULL && len <= 2)
	{
		i = -1;
		while (tmp && ++i < len)
			tmp = tmp->next;
		return ((t_lineterm*)tmp);
	}
	else if (tmp != NULL && len > 2)
	{
		while (tmp && len-- > 0)
			tmp = tmp->next;
		return ((t_lineterm *)tmp);
	}
	return (NULL);
}

void 			ft_replace_exp_hist(t_termc *tsh)
{
	dlist 		tmp;

	if ((!tsh->histlist && !tsh->histlist->end) || tsh->quote_no)
		return ;
	tmp.begin = NULL;
	tmp.end = NULL;
	ft_dupdlnk(tsh->line, &tmp);
	ft_clean_line(tsh);
	if (tsh->quotes)
		while (tmp.begin && tmp.begin->index == 0)
			tmp.begin = tmp.begin->next;
	while (tmp.begin)
	{
		if (!ft_replace_pattern(&tmp, tsh))
		{
			push_dupdlst(tsh->line, tmp.begin->c, tmp.begin->s_pos,\
				tmp.begin->index);
			tmp.begin = tmp.begin->next;
		}
	}
	ft_freedlnk(&tmp);
}
