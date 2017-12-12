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

int    ft_add_file_history_no_flag(t_termc *tsh)
{
    int fd;
    t_history *begin;

    if ((fd = open("~/.21sh_history", (O_WRONLY | O_CREAT | O_APPEND), 0777)) < 0)
        return (0);
    begin = tsh->from_hist->begin;
    if (begin)
    {
        while (begin)
        {
            write(fd, begin->data, ft_strlen(begin->data));
            write(fd, "\n", 1);
            begin = begin->next;
        }
    }
    close(fd);
    return (1);
}

static inline void     ft_add_file_history_split(t_history *begin, int fd, int res)
{
    int     ret;
    char    *line;
    int     i;

    i = 0;
    line = NULL;
    while ((ret = get_next_line(fd, &line)) > 0)
    {
        if (i++ >= res - 500)
        {
            write(fd, begin->data, ft_strlen(begin->data));
            write(fd, "\n", 1);
            begin = begin->next;
        }
        free(line);
    }
    if (i == 0)
    {
        while (begin)
        {
            write(fd, begin->data, ft_strlen(begin->data));
            write(fd, "\n", 1);
            begin = begin->next;
        }

    }
}

int     ft_add_file_history(t_termc *tsh)
{
    int         fd;
    int         res;
    t_history   *begin;

    if ((fd = open(tsh->from_hist->pwd, (O_WRONLY | O_CREAT), 0777)) < 0)
        return (0);
    begin = NULL;
    begin = tsh->from_hist->begin;
    if (begin)
    {
        res = ft_count_history(tsh->from_hist->pwd);
        ft_add_file_history_split(begin, fd, res);
    }
    close(fd);
    return (1);
}

void	ft_add_tmp_history(t_termc *tsh, const char *str)
{
    int flag;
    int i;

    flag = 0;
    i = -1;
    while (str[++i])
    {
        if (str[i] >= 33 && str[i] <= 126)
            flag = 1;
    }
    if (flag && (!tsh->from_hist->end ||
        ft_strcmp(tsh->from_hist->end->data, str) != 0))
    {
        ft_fill_back_hlst(tsh->from_hist, str);
        tsh->nbr_hist++;
    }
}
