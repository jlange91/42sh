/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 15:45:20 by jlange            #+#    #+#             */
/*   Updated: 2018/01/23 15:45:35 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"

char		**ft_var_local(char **arg)
{
	static char **local = NULL;

	if (arg)
		local = arg;
	return (local);
}

t_termc		*ft_ret_tsh(t_termc **arg)
{
	static t_termc *tsh = NULL;

	if (arg && *arg)
		tsh = *arg;
	return (tsh);
}
