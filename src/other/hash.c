/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 14:17:05 by vmartins          #+#    #+#             */
/*   Updated: 2018/01/23 15:23:31 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/hash.h"
#include "../../inc/sh21.h"

static	inline	t_hash	*ft_new_maillon(char *cmd, char *path)
{
	t_hash				*new;

	if ((new = (t_hash *)malloc(sizeof(t_hash))) == NULL)
		return (NULL);
	new->cmd = ft_strdup(cmd);
	new->path = ft_strdup(path);
	new->next = NULL;
	return (new);
}

int						ft_calc_hash(char *word)
{
	int					i;
	int					ret;

	i = 0;
	ret = 0;
	while (word[i] != '\0')
	{
		ret += word[i];
		i++;
	}
	ret %= SIZEH;
	return (ret);
}

void					ft_add_hash_next(t_hash *hash, char *cmd, char *path)
{
	t_hash		*tmp;

	tmp = hash;
	while (tmp)
	{
		if (ft_strcmp(cmd, tmp->cmd) == 0)
		{
			if (tmp->path)
				free(tmp->path);
			tmp->path = ft_strdup(path);
			return ;
		}
		tmp = tmp->next;
	}
	tmp = hash;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = ft_new_maillon(cmd, path);
}

int						ft_add_hash(char *cmd, char *path)
{
	int					i;
	int					nbrhash;
	t_shell				*sh;
	t_hash				*hash;

	i = 0;
	if (!cmd || !path)
		return (0);
	sh = ft_ret_sh(NULL);
	hash = sh->hash;
	nbrhash = ft_calc_hash(cmd);
	if (hash[nbrhash].cmd == NULL)
	{
		hash[nbrhash].cmd = ft_strdup(cmd);
		hash[nbrhash].path = ft_strdup(path);
		hash[nbrhash].next = NULL;
	}
	else if (hash[nbrhash].cmd != NULL)
		ft_add_hash_next(&hash[nbrhash], cmd, path);
	return (nbrhash);
}

char					*ft_return_hash(char *cmd)
{
	int					nbrhash;
	t_shell				*sh;
	t_hash				*hash;
	t_hash				*tmp;

	nbrhash = ft_calc_hash(cmd);
	sh = ft_ret_sh(NULL);
	hash = sh->hash;
	if (hash[nbrhash].cmd)
	{
		tmp = &hash[nbrhash];
		while (tmp)
		{
			if (ft_strcmp(cmd, tmp->cmd) == 0)
				return (tmp->path);
			tmp = tmp->next;
		}
	}
	return (NULL);
}
