/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 16:21:08 by vmartins          #+#    #+#             */
/*   Updated: 2018/01/30 16:21:10 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H
# include "../libft/include/libft.h"
# define SIZEH 1000

typedef struct	s_hash
{
	char			*cmd;
	char			*path;
	struct s_hash	*next;
}				t_hash;

int				ft_calc_hash(char *word);
char			*ft_return_hash(char *cmd);
int				ft_add_hash(char *cmd, char *path);

#endif
