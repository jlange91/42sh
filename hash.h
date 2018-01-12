/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 12:02:59 by vmartins          #+#    #+#             */
/*   Updated: 2017/12/19 12:03:07 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H
# include "../libft/libft.h"

typedef struct  s_hash
{
    char            *cmd;
    char            *path;
    struct s_hash   *next;
}               t_hash;

int     hash_table(char *cmd, t_hash *hash);

#endif
