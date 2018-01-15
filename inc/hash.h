/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 12:02:59 by vmartins          #+#    #+#             */
/*   Updated: 2018/01/15 18:41:46 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H
# include "../libft/include/libft.h"
# define SIZEH 1000


typedef struct  s_hash
{
    char            *cmd;
    char            *path;
    struct s_hash   *next;
}               t_hash;

int		ft_calc_hash(char *word);
char 	*ft_return_hash(char *cmd);
int     ft_add_hash(char *cmd, char *path);
void    ft_free_hash(void);

#endif
