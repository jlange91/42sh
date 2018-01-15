#include "../../inc/sh21.h"
#include "../../inc/built_in.h"
#include "../../inc/line_edition.h"

int    ft_display_history(hlist *histlist)
{
	t_history 	*begin;
	t_history 	*tmp;
	int			i;

	begin = histlist->begin;
	if (!begin)
		return (1);
	tmp = histlist->begin;
	i = 0;
	while (tmp)
	{
		if (tmp->print)
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

static inline void 	ft_del_elem_history_split(int index, hlist *histlist)
{
	t_history *tmp;

	tmp = histlist->begin;
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
}

static inline int ft_del_elem_history(char *av, hlist *histlist, int flag)
{
	int index;
	int i;

	if (flag == 0)
	{
		i = (av[0] == 'd') ? 1 : 0;
		index = ft_atoi(&av[i]);
		if (!ft_only_digit(&av[i + 1]))
			return (ft_error_history(&av[i], 0));
		else if (index < histlist->begin->index || index > histlist->end->index)
			return (ft_error_history(&av[i], 0));
		else
			ft_del_elem_history_split(index, histlist);
	}
	else
	{
		ft_free_history(histlist);
		histlist->ecrase_hist = 1;
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

static inline int ft_end(char *av1, int flag)
{
	int i;

	i = 0;
	while (av1[i])
	{
		if ((av1[i] == 'c' || av1[i] == 's') && flag == 1)
			return (1);
		if (av1[i] == 'c' && flag == 2)
			return (1);
		if ((av1[i] == 'p' || av1[i] == 's') && (flag == 3 || flag == 4
			|| flag == 5))
			return(1);
		i++;
	}
	return (0);
}

static inline int ft_execute_opt(char *av1, char **av, hlist *hist)
{
	int i;

	i = 0;
	while (av1[++i])
		if (av1[i] == 'c')
		{
			ft_del_elem_history(av1, hist, 1);
			break ;
		}
	i = 0;
	while (av1[++i])
	{
		if (av1[i] == 'p')
		{
			if (ft_end(av1, 1))
				continue ;
			else if (av && av[2] != NULL)
				ft_opt_p(av, hist);
		}
		if (av1[i] == 's')
		{
			if (ft_end(av1, 2))
				continue ;
			else if (av && av[2] != NULL)
				ft_opt_s(av, hist);
		}
		if (av1[i] == 'w')
		{
			if (ft_end(av1, 3))
				continue ;
			else if (av && av[2] != NULL)
				ft_opt_w(av[2], hist->begin, hist);
		}
		if (av1[i] == 'a')
		{
			if (ft_end(av1, 4))
				continue ;
			else if (av && av[2] != NULL)
				ft_opt_a(av[2], hist->begin, hist);
		}
		if (av1[i] == 'r')
		{
			if (ft_end(av1, 5))
				continue ;
			else if (av && av[2] != NULL)
				ft_opt_r(av[2], hist->begin, hist);
		}
	}
	return (0);
}

int history(t_cmd *cmd)
{
	t_termc *tsh;

    tsh = ft_ret_tsh(NULL);
    if (cmd->av[1] == NULL)
        return (ft_display_history(tsh->histlist));
	else if (cmd->av[1] != NULL && ft_only_digit(cmd->av[1]))
		return (ft_find_index_history(cmd->av[1], tsh->histlist));
	else
	{
		if (cmd->av[1] && cmd->av[1][0] != '-')
			return (ft_error_history(cmd->av[1], 4));
		if (ft_check_option(cmd->av[1], cmd->av[2]))
			return (1);
		if (cmd->av[1][1] == 'd')
		{
			if (cmd->av[1][2] != 0)
				return (ft_del_elem_history(&cmd->av[1][2], tsh->histlist, 0));
			return (ft_del_elem_history(cmd->av[2], tsh->histlist, 0));
		}
		if (ft_execute_opt(cmd->av[1], cmd->av, tsh->histlist))
			return (1);
	}
	return (0);
}
