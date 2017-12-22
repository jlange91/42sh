#include "../../inc/sh21.h"
#include "../../inc/built_in.h"
#include "../../inc/line_edition.h"

int    ft_display_history(hlist *histfile)
{
	t_history 	*begin;
	t_history 	*tmp;
	int			i;

	begin = histfile->begin;
	if (!begin)
		return (1);
	tmp = histfile->begin;
	i = 0;
	while (tmp)
	{
		if (tmp->print && tmp->index != -1)
			tmp->index = ++i;
		tmp = tmp->next;
	}
	while(begin)
	{
		if (begin->print)
		{
			ft_putnbr(begin->index);
			ft_putchar(' ');
			ft_putendl(begin->data);
		}
		begin = begin->next;
	}
	return (0);
}

int 		ft_error_history(char *av, int flag)
{
	ft_putstr_fd("42sh: history: ", 2);
	ft_putstr_fd(av, 2);
	if (!flag)
		ft_putendl_fd(": history position out of range", 2);
	else
	{
		ft_putendl_fd(": invalid option", 2);
		ft_putstr_fd("42sh: history: ", 2);
		ft_putstr_fd("usage: ", 2);
		ft_putstr_fd("history [-c] [-d offset] [n] or history -awr", 2);
		ft_putendl_fd("[filename] or history -ps arg [arg...]", 2);
	}
	return (1);
}

void 	ft_del_elem_history_split(int index, hlist *histfile)
{
	t_history *tmp;

	tmp = histfile->begin;
	while (tmp)
	{
		if (tmp->index == index)
		{
			tmp->print = 0;
			while (tmp)
			{
				if (tmp->index != 1)
					tmp->index--;
				tmp = tmp->next;
			}
			break;
		}
		tmp = tmp->next;
	}
	ft_display_history(histfile);
}

static inline int ft_del_elem_history(char *av, hlist *histfile, int flag)
{
	int index;
	int i;

	if (flag == 0)
	{
		i = 0;
		if (av[0] == '-')
			while (av[i] && !ft_isdigit(av[i]))
				i++;
		index = ft_atoi(&av[i]);
		if (!ft_only_digit(&av[i]))
			return (ft_error_history(&av[i], 0));
		else if (index < histfile->begin->index || index > histfile->end->index)
			return (ft_error_history(&av[i], 0));
		else
			ft_del_elem_history_split(index, histfile);
	}
	else
	{
		ft_free_history(histfile);
		histfile->ecrase_hist = 1;
	}
	return (0);
}

static inline int ft_find_index_history(char *av, hlist *hist)
{
	t_history 	*begin;
	int 		index;

	index = ft_atoi(av);
	begin = hist->end;
	while (begin)
	{
		if (index == 1)
			break;
		index--;
		begin = begin->prev;
	}
	if (index > hist->end->index)
		return (ft_display_history(hist));
	else if (index < hist->begin->index)
		return (ft_error_history(av, 1));
	while (begin)
	{
		ft_putnbr(begin->index);
		ft_putchar(' ');
		ft_putendl(begin->data);
		begin = begin->next;
	}
	return (0);
}

// static inline int ft_good_opt(char *av, char opt[5], int flag)
// {
// 	int i;
// 	int j;
//
// 	i = 0;
// 	j = 0;
// 	while (av[++i])
// 	{
// 		if (av[i] != 'a' && av[i] != 'n' && av[i] != 'r' && av[i] != 'w'
// 			&& av[i] != 'p' && av[i] != 's')
// 			return (0);
// 		if ((av[i] == 'a' || av[i] == 'n' || av[i] == 'r' || av[i] == 'w'
// 			|| av[i] == 'p' || av[i] == 's') && flag)
// 		{
// 			opt[j] = av[i];
// 			j++;
// 		}
// 	}
// 	opt[j]= '\0';
// 	return (3);
// }
//
// static inline int ft_anrw(char *av1, char *av2, hlist *hist, char **av)
// {
// 	char 	opt[5];
// 	int		i;
// 	t_history *begin;
//
// 	begin = hist->begin;
// 	if (ft_good_opt(av1, opt, 1) != 3)
// 		return (1);
// 	i = 0;
// 	while (opt[i])
// 	{
// 		if (opt[i] == 'a')
// 			ft_opt_a(av2, begin, hist);
// 		if (opt[i] == 'r')
// 			ft_opt_r(av2, begin, hist);
// 		if (opt[i] == 'w')
// 			ft_opt_w(av2, begin, hist);
// 		if (opt[i] == 'p')
// 			ft_opt_p(av, hist);
// 		if (opt[i] == 's')
// 			ft_opt_s(av, hist);
// 		i++;
// 	}
// 	return (0);
// }


static inline int ft_option_del(char *av, hlist *hist)
{
	int i;

	i = 0;
	while (av[i])
	{
		if (av[0] != '-')
			return (-1);
		else if (av[i] == 'd')
			ft_del_elem_history(av, hist, 0);
		else if (av[i] == 'c')
			return (2);
		// else if (av[1] == 'a' || av[1] == 'r' || av[1] == 'w' || \
		// 	av[1] == 'p'|| av[1] == 's')
			// return (3);
		i++;
	}
	return (0);
}

int history(t_cmd *cmd)
{
	t_termc *tsh;
	int 	opt;

    tsh = ft_ret_tsh(NULL);
    if (cmd->av[1] == NULL)
        return (ft_display_history(tsh->histfile));
	else if (cmd->av[1] != NULL && ft_only_digit(cmd->av[1]))
		return (ft_find_index_history(cmd->av[1], tsh->histfile));
	else if (cmd->av[1] != NULL && cmd->av[2] == NULL)
	{
		opt = ft_option_del(cmd->av[1], tsh->histfile);
		// if (opt == 1)
		// 	return (ft_del_elem_history(cmd->av[1], tsh->histfile, 0));
		// else if (opt == 2)
		// 	return (ft_del_elem_history(NULL, tsh->histfile, 1));
		// else if (opt == 3 && cmd->av[2] != NULL)
		// 	return (ft_anrw(cmd->av[1],cmd->av[2], tsh->histfile, cmd->av));
	}
    return (1);
}
