/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_escape.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 02:01:50 by jlange            #+#    #+#             */
/*   Updated: 2018/01/22 15:47:38 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"

static	inline	void	init_escape_tab(char *escape_tab)
{
	escape_tab[0] = '!';
	escape_tab[1] = '"';
	escape_tab[2] = '$';
	escape_tab[3] = '&';
	escape_tab[4] = '\'';
	escape_tab[5] = '(';
	escape_tab[6] = ')';
	escape_tab[7] = ',';
	escape_tab[8] = ':';
	escape_tab[9] = ';';
	escape_tab[10] = '<';
	escape_tab[11] = '=';
	escape_tab[12] = '>';
	escape_tab[13] = '?';
	escape_tab[14] = '@';
	escape_tab[15] = '[';
	escape_tab[16] = '\\';
	escape_tab[17] = ']';
	escape_tab[18] = '^';
	escape_tab[19] = '`';
	escape_tab[20] = '{';
	escape_tab[21] = '|';
	escape_tab[22] = '}';
}

static	inline	void	init_escape_tab2(char *escape_tab)
{
	escape_tab[23] = ' ';
	escape_tab[24] = '\t';
	escape_tab[25] = '\n';
	escape_tab[26] = '\0';
}

static	inline	char	*add_backslah(char *str, int index)
{
	char				*ret;
	int					i;

	i = -1;
	if ((ret = (char *)malloc(sizeof(char ) * (ft_strlen(str) + 2))) == NULL)
	{
		ft_putendl_fd("Error Malloc", 2);
		exit(1);
	}
	while (++i < index)
		ret[i] = str[i];
	ret[i] = '\\';
	ret[i + 1] = '\0';
	ret = ft_strcat(ret, &str[i]);
	return (ret);
}

char					*ft_add_escape(char *str)
{
	char				tab[27];
	int					i;
	int					j;

	init_escape_tab(tab);
	init_escape_tab2(tab);
	i = -1;
	while (str[++i])
	{
		j = -1;
		while (tab[++j])
		{
			if (str[i] == tab[j])
			{
				str = ft_replace_str(add_backslah(str, i), str);
				++i;
				break ;
			}
		}
	}
	return (str);
}
