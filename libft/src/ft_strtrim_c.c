/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_c.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastres <mcastres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 12:18:18 by mcastres          #+#    #+#             */
/*   Updated: 2018/01/24 18:52:44 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strtrim_c(char const *s, char c)
{
	char	*str;
	int		i;
	int		j;
	int		len;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	len = ft_strlen(s) - 1;
	while (s[i] == c)
		i++;
	if (!(s[i]) || ft_strlen(s) == 0 || !s)
		return (ft_strsub(s, 0, 0));
	while (s[len] == c)
		len--;
	if (!(str = (char *)malloc(sizeof(*str) * (len - i) + 2)))
		return (NULL);
	while (i < len + 1)
		str[j++] = s[i++];
	str[j] = '\0';
	return (str);
}
