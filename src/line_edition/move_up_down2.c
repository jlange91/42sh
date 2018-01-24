/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_up_down2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 19:00:18 by stvalett          #+#    #+#             */
/*   Updated: 2018/01/22 19:01:20 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"

void			ft_move_down_line_auto(t_lineterm *end, t_termc *tsh)
{
	if (tsh->auto_active == 1 || tsh->multiauto_active == 1)
	{
		ft_auto_down_up(end, tsh, 1);
		return ;
	}
}
