/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_autocompletion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 19:03:13 by vmartins          #+#    #+#             */
/*   Updated: 2018/01/23 17:24:14 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/autocompletion.h"

/*
**@function
**@param
**@return
*/

void			ft_fill_back_autocompl(t_auto *autoc, char *file, int index)
{
	t_autocompl	*new;

	new = NULL;
	if ((new = (t_autocompl *)malloc(sizeof(*new))) == NULL)
	{
		ft_putendl_fd("Error malloc", 2);
		exit(0);
	}
	new->data = ft_strdup(file);
	new->index = index;
	new->next = NULL;
	new->prev = autoc->end;
	if (autoc->end)
		autoc->end->next = new;
	else
		autoc->begin = new;
	autoc->end = new;
}

/*
**@function
**@param
**@return
*/

char			*ft_after_antislash(char *str, int *ret)
{
	char		*tmp;
	int			i;
	int			enter;

	i = 0;
	enter = 0;
	tmp = NULL;
	i = ft_strlen(str) - 1;
	while (str[i] && str[i] != '/' && str[i] != ' ')
	{
		if (i == 0)
			return (tmp);
		enter = 1;
		i--;
	}
	i++;
	*ret = i;
	if (!enter)
		return (tmp);
	tmp = ft_strdup(&str[i]);
	return (tmp);
}

/*
**@function
**@param
**@return
*/

int				ft_count(t_auto *select)
{
	t_autocompl	*begin;
	int			count;

	begin = select->begin;
	count = 0;
	while (begin)
	{
		count++;
		begin = begin->next;
	}
	return (count);
}

/*
**@function
**@param
**@return
*/

int				ft_not_str(char *str, t_termc *tsh)
{
	if (str[0] == '\0')
	{
		ft_clean_line(tsh);
		tsh->auto_active = 0;
		tsh->multiauto_active = 0;
		return (1);
	}
	return (0);
}
