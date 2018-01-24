/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ret_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 16:38:35 by jlange            #+#    #+#             */
/*   Updated: 2018/01/19 16:38:38 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"

char	*ft_ret_word(char *line)
{
	char *word;

	word = (char*)malloc(sizeof(char) * (ft_count_char_word(line) + 1));
	word[0] = '\0';
	ft_fill_word(line, word);
	return (word);
}
