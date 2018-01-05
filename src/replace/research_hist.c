#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"
#include "../../inc/globbing.h"
#include "../../inc/sh21.h"

static void 	*ft_skip_hist(t_history *end, int len, int flag, char *data)
{
	if (!flag)
		while (end && len-- > 1)
			end = end->prev;
	else if (flag == 1)
		while (end && end->index != len)
			end = end->prev;
	else if (flag == 2)
		while (end && ft_strncmp(data, end->data, ft_strlen(data)))
			end = end->prev;
	return ((t_history *)end);
}

static inline char 	*ft_str(int *count, t_lineterm *begin, int flag)
{
	char 		*tmp;

	tmp = ft_strdup(&begin->c);
	*count = *count + 1;
	while ((begin = begin->next))
	{
		if (!flag && !ft_isdigit(begin->c))
			break;
		else if (flag == 1 && begin->c == ' ')
			break;
		else if (flag == 2 && begin->c == '?')
			break;
		*count = *count + 1;
		tmp = ft_free_join(tmp, &begin->c, 'L');
	}
	if (flag == 2 && !begin)
	{
		free(tmp);
		return (NULL);
	}
	return (tmp);
}

int 	ft_find(t_termc *tsh, t_lineterm *begin, int *count)
{
	int 		ret;
	char 		*tmp;
	t_history 	*end;

	tmp = ft_str(count, begin, 0);
	ret = ft_atoi(tmp);
	if (!ret || ret > ft_count_from_file(tsh->histlist->pwd))
		return (ft_returnfree(tmp, 0, 'f'));
	else
	{
		end = ft_skip_hist(tsh->histlist->end, ret, 0, NULL);
		ft_cpy_to_line(end->data, tsh);
		return (ft_returnfree(tmp, 1, 'f'));
	}
	return (0);
}

int 	ft_find2(t_termc *tsh, t_lineterm *begin, int *count)
{
	int 		ret;
	char 		*tmp;
	t_history 	*end;

	tmp = ft_str(count, begin, 1);
	if (begin->c >= '0' && begin->c <= '9')
	{
		ret = ft_atoi(tmp);
		if (!ret || ret > tsh->histlist->end->index)
			return (ft_returnfree(tmp, 0, 'f'));
		end = ft_skip_hist(tsh->histlist->end, ret, 1, NULL);
		ft_cpy_to_line(end->data, tsh);
		return (ft_returnfree(tmp, 1, 'f'));
	}
	else
	{
		if ((end = ft_skip_hist(tsh->histlist->end, 0, 2, tmp)) == NULL)
			return (ft_returnfree(tmp, 0, 'f'));
		ft_cpy_to_line(end->data, tsh);
		return (ft_returnfree(tmp, 1, 'f'));
	}
	return (0);
}

int 	ft_find3(t_termc *tsh, t_lineterm *begin, int *count)
{
	char 		*tmp;
	t_history 	*end;

	if ((tmp = ft_str(count, begin, 2)) == NULL)
		return (0);
	*count = *count + 1;
	if ((end = ft_skip_hist(tsh->histlist->end, 0, 2, tmp)) == NULL)
		return (ft_returnfree(tmp, 0, 'f'));
	ft_cpy_to_line(end->data, tsh);
	return (ft_returnfree(tmp, 1, 'f'));
}
