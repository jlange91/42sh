/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 14:16:56 by vmartins          #+#    #+#             */
/*   Updated: 2018/01/23 15:17:06 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/autocompletion.h"

static	void	ft_split_key(long *c, int *stp, char k)
{
	*c = (k == 68 && *stp == 1) ? LEFT : *c;
	*c = (k == 67 && *stp == 1) ? RIGHT : *c;
	*c = (k == 65 && *stp == 1) ? UP : *c;
	*c = (k == 66 && *stp == 1) ? DOWN : *c;
	*c = (k == -102 && *stp == 3) ? OPT_V : *c;
	*c = (k == -89 && *stp == 1) ? OPT_C : *c;
	*c = (k == -120 && *stp == 3) ? OPT_X : *c;
	*c = (k == 72 && *stp == 1) ? HOME : *c;
	*c = (k == 70 && *stp == 1) ? END : *c;
	*c = (k == 68 && *stp == 2) ? OPT_F : *c;
	*c = (k == 67 && *stp == 2) ? OPT_B : *c;
	*c = (k == 65 && *stp == 2) ? OPT_UP : *c;
	*c = (k == 66 && *stp == 2) ? OPT_DOWN : *c;
	*c = (k == 68 && *stp == 4) ? MAJ_LEFT : *c;
	*c = (k == 67 && *stp == 4) ? MAJ_RIGHT : *c;
	*stp = 0;
}

int				ft_what_key(long *c, int *stp, char k)
{
	if (k == 27 || k == -30 || k == -61)
	{
		return ((*stp = *stp + 1));
		return (1);
	}
	if ((k == 91 && *stp) || (k == -119 && *stp != 3) ||
			(k == -120 && *stp != 3))
	{
		if (k == -120 || k == -119)
			*stp = 3;
		return (*stp);
	}
	if (*stp && (k == 49 || k == 59 || k == 50))
	{
		return ((*stp = 4));
		return (1);
	}
	if (*stp && (k == 68 || k == 67 || k == 65 || k == 66 || k == -102\
				|| k == 72 || k == 70 || k == -120 || k == -89))
		ft_split_key(c, stp, k);
	else
		*c = k;
	return (0);
}
