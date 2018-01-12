/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 14:17:05 by vmartins          #+#    #+#             */
/*   Updated: 2017/12/18 14:23:45 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

#define SIZEH 1000

t_hash					*ft_new_maillon(char *cmd)
{
	t_hash *new;

	if ((new = (t_hash *)malloc(sizeof(t_hash))) == NULL)
		return (NULL);
	new->cmd = ft_strdup(cmd);
	new->path = NULL;
	new->next = NULL;
	return (new);
}

int						hash_table(char *cmd, t_hash hash[SIZEH])
{
	int		i;
	int		nbrhash;
	t_hash	*tmp;

	i = 0;
	nbrhash = 0;
	while (cmd[i] != '\0')
	{
		nbrhash += cmd[i];
		i++;
	}
	nbrhash %= SIZEH;
	if (hash[nbrhash].cmd == NULL)
	{
		hash[nbrhash].cmd = ft_strdup(cmd);
		hash[nbrhash].next = NULL;
	}
	else if (hash[nbrhash].cmd != NULL)
	{
		tmp = &hash[nbrhash];
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_new_maillon(cmd);
	}
	return (nbrhash);
}



char 					*return_hash(char *cmd, t_hash hash[SIZEH])
{
	int		i;
	int		nbrhash;
	t_hash 	*tmp;

	i = 0;
	nbrhash = 0;
	while (cmd[i] != '\0')
	{
		nbrhash += cmd[i];
		i++;
	}
	if (hash[nbrhash].cmd)
	{
		tmp = &hash[nbrhash];
		while (tmp)
		{
			if (ft_strcmp(cmd, tmp->cmd) == 0)
				return (tmp->cmd);
			tmp = tmp->next;
		}
	}
	return (NULL);
}

int						main(void)
{
	int		i;
	int		j;
	t_hash	hash[SIZEH];

	i = 0;
	j = 0;
	ft_memset(hash, 0, sizeof(hash));
	i = hash_table("cba", hash);
	i = hash_table("abc", hash);
	i = hash_table("cba", hash);
	i = hash_table("abc", hash);
	i = hash_table("bca", hash);
	i = hash_table("acb", hash);
	i = hash_table("toto", hash);
	i = hash_table("otot", hash);
	while (j < 1000)
	{
		if (hash[j].cmd != NULL)
		{
			//ft_putendl("NEW");
			//ft_putendl(hash[j].cmd);
			t_hash tmp;

			tmp = hash[j];
			if (tmp.next != NULL)
			{
				while (tmp.next)
				{
					tmp = *tmp.next;
					//ft_putendl(tmp.cmd);
				}
			}
		}
		j++;
	}
	ft_putstr(return_hash("abc", hash));
	return (0);
}
