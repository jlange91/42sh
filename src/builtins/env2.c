/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 20:46:05 by jlange            #+#    #+#             */
/*   Updated: 2017/11/16 13:27:17 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"
#include "../../inc/built_in.h"

static inline int	check_name_value(char *av)
{
	int i;

	i = 0;
	while (av[i])
	{
		if (av[i] == '=')
			return (1);
		else if (!ft_isalnum(av[i]))
			return (0);
		++i;
	}
	return (0);
}

static inline void	add_env_arg(char *av, char ***env)
{
	char	*name;
	char	*value;
	int		i;

	i = 0;
	while (av[i] && av[i] != '=')
		i++;
	value = &av[i + 1];
	name = ft_strndup(av, i);
	*env = ft_replace_env(ft_setenv(name, value, *env), *env);
	free(name);
}

int					env_skip_name_value(char **av, char ***env)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (av[i] && check_name_value(av[i]))
	{
		add_env_arg(av[i], env);
		++i;
	}
	return (i);
}
