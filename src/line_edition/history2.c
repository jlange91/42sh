#include "../../inc/line_edition.h"

void	ft_free_history(hlist *history)
{
	t_history	*tmp;
	t_history	*del;

	tmp = history->end;
	if (tmp != NULL)
	{
		while (tmp)
		{
			del = tmp;
			tmp = tmp->prev;
			free(del->data);
			free(del);
		}
		history->end = NULL;
		history->current = NULL;
		history->begin = NULL;
	}
}

int     ft_add_file_history(t_termc *tsh)
{
    int         fd;
    t_history   *begin;

    if ((fd = open(tsh->histfile->pwd, (O_WRONLY | O_CREAT | O_TRUNC), 0777)) < 0)
        return (0);
    begin = NULL;
    begin = tsh->histfile->begin;
    if (begin)
	{
		while (begin)
		{
			if (begin->index != -1)
			{
				write(fd, begin->data, ft_strlen(begin->data));
				write(fd, "\n", 1);
			}
			begin = begin->next;
		}
	}
    close(fd);
    return (1);
}

void	ft_add_tmp_history(t_termc *tsh, const char *str)
{
    int flag;
    int i;
	int index;

    flag = 0;
    i = -1;
    while (str[++i])
    {
        if (str[i] >= 33 && str[i] <= 126)
            flag = 1;
    }
    if (flag && (!tsh->histfile->end ||
        ft_strcmp(tsh->histfile->end->data, str) != 0))
	{
		index = (!tsh->histfile->end) ? 1 : tsh->histfile->end->index + 1;
		push_backhist(tsh->histfile, str, index, 1);
	}
}
