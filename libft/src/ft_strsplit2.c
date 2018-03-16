/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 15:29:03 by vmartins          #+#    #+#             */
/*   Updated: 2017/03/31 15:49:52 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	ft_count(char *s)
{
	int count;
	int i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n' && s[i])
		{
			count++;
			while (s[i] != ' ' && s[i] != '\t' && s[i] != '\n' && s[i])
				i++;
		}
		else
			i++;
	}
	return (count);
}

static char	*ft_create_wrd(char *s, int *i)
{
	int		index;
	char	*tmp;

	if (!s)
		return (NULL);
	if ((tmp = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))) == NULL)
		return (NULL);
	index = 0;
	while (s[*i] != ' ' && s[*i] != '\t' && s[*i] != '\n' && s[*i] && s[*i])
	{
		tmp[index] = s[*i];
		index++;
		*i = *i + 1;
	}
	tmp[index] = '\0';
	return (tmp);
}

char		**ft_strsplit2(char const *s)
{
	int		word;
	int		i;
	int		j;
	char	**str;

	if (!s)
		return (NULL);
	word = ft_count((char *)s);
	if ((str = (char **)malloc(sizeof(*str) * (word + 1))) == NULL)
		return (NULL);
	i = 0;
	while ((s[i] == ' ' || s[i] == '\t' || s[i] == '\n') && s[i])
		i++;
	j = 0;
	while (j < word)
	{
		if ((s[i] == ' ' || s[i] == '\t' || s[i] == '\n') && s[i])
			while ((s[i] == ' ' || s[i] == '\t' || s[i] == '\n') && s[i])
				i++;
		str[j] = ft_create_wrd((char *)s, &i);
		j++;
	}
	str[j] = NULL;
	return (str);
}
