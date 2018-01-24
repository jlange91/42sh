#include "../../inc/sh21.h"

static inline void	free_hash(t_hash *hash)
{
	while (hash)
	{
		if (hash->cmd)
			free(hash->cmd);
		if (hash->path)
			free(hash->path);
		hash = hash->next;
	}
}

void				ft_reinit_hash(void)
{
	t_shell	*sh;
	t_hash	*hash;
	int		i;

	sh = ft_ret_sh(NULL);
	hash = sh->hash;
	i = 0;
	while (i < SIZEH)
	{
		if (hash[i].cmd)
			free(hash[i].cmd);
		if (hash[i].path)
			free(hash[i].path);
		if (hash[i].next)
			free_hash(&hash[i]);
		++i;
	}
	ft_memset(&hash, 0, sizeof(hash));
}
