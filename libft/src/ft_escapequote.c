/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_escapequote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastres <mcastres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 11:46:42 by mcastres          #+#    #+#             */
/*   Updated: 2017/09/15 16:29:35 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_escapequote(char const *s)
{
	char	*str;
	size_t	i;
	size_t	len;
	size_t	j;

	if (!s)
		return (NULL);
	ft_tabtospace((char *)s);
	i = 0;
	j = 0;
	len = ft_strlen(s) - 1;
	while ((s[i] == 34 || s[i] == 39 || s[i] == '\n'
	|| s[i] == '\t') && s[i])
		i++;
	if (!(s[i]) || ft_strlen(s) == 0 || !s)
		return (ft_strsub(s, 0, 0));
	while ((s[len] == 34 || s[len] == 39
		|| s[len] == '\n' || s[len] == '\t') && s[len])
		len--;
	if (!(str = (char *)malloc(sizeof(*str) * (len - i) + 2)))
		return (NULL);
	while (i < len + 1)
		str[j++] = s[i++];
	str[j] = '\0';
	return (str);
}
