/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reinit_hash.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 16:38:35 by jlange            #+#    #+#             */
/*   Updated: 2018/01/24 16:39:05 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"

static inline void	free_hash(t_hash *hash)
{
	int		count;
	t_hash	*tmp;

	tmp = NULL;
	count = 0;
	while (hash)
	{
		tmp = hash;
		if (hash->cmd)
		{
			free(hash->cmd);
			hash->cmd = NULL;
		}
		if (hash->path)
		{
			free(hash->path);
			hash->path = NULL;
		}
		hash = hash->next;
		if (count > 0)
			free(tmp);
		++count;
	}
}

void				ft_reinit_hash(void)
{
	t_shell	*sh;
	t_hash	*hash;
	int		i;

	sh = ft_ret_sh(NULL);
	hash = sh->hash;
	i = -1;
	while (++i < SIZEH)
	{
		if (hash[i].cmd)
		{
			free(hash[i].cmd);
			hash[i].cmd = NULL;
		}
		if (hash[i].path)
		{
			free(hash[i].path);
			hash[i].path = NULL;
		}
		if (hash[i].next)
		{
			free_hash(&hash[i]);
			hash[i].next = NULL;
		}
	}
}
