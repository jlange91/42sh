/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keep_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebrito <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 16:14:58 by adebrito          #+#    #+#             */
/*   Updated: 2017/11/22 13:31:37 by adebrito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_select		*keep_term(t_select *select)
{
	static	t_select	*temp = NULL;

	if (select)
		temp = select;
	return (temp);
}
