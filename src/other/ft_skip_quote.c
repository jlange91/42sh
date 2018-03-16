/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 16:02:44 by vmartins          #+#    #+#             */
/*   Updated: 2018/01/22 16:03:02 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_skip_quote(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '\'')
	{
		while (str[i] != '\'')
			i++;
		return (i);
	}
	else
		return (0);
}

int		ft_skip_dquote(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '"')
	{
		while (str[i] != '"')
		{
			if (str[i] == '\\')
				i++;
			i++;
		}
		return (i);
	}
	else
		return (0);
}
