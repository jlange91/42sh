/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_glob.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 18:27:12 by stvalett          #+#    #+#             */
/*   Updated: 2018/01/19 18:31:54 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/globbing.h"

static	void	ft_init_escape_tab(char *escape_tab)
{
	escape_tab[0] = '!';
	escape_tab[1] = '"';
	escape_tab[2] = '$';
	escape_tab[3] = '&';
	escape_tab[4] = '\'';
	escape_tab[5] = '(';
	escape_tab[6] = ')';
	escape_tab[7] = '*';
	escape_tab[8] = ',';
	escape_tab[9] = ':';
	escape_tab[10] = ';';
	escape_tab[11] = '<';
	escape_tab[12] = '=';
	escape_tab[13] = '>';
	escape_tab[14] = '?';
	escape_tab[15] = '@';
	escape_tab[16] = '[';
	escape_tab[17] = '\\';
	escape_tab[18] = ']';
	escape_tab[19] = '^';
	escape_tab[20] = '`';
	escape_tab[21] = '{';
	escape_tab[22] = '|';
	escape_tab[23] = '}';
	escape_tab[24] = '\0';
}

void			ft_save_word(t_glob *glob, char **str, int len)
{
	int			i;
	struct stat	info;

	i = 0;
	while (i < len)
	{
		ft_memset(&info, 0, sizeof(info));
		if (stat(glob[i].path, &info) != -1)
		{
			if (glob[i].path != NULL && *str == NULL)
				*str = ft_strjoin(glob[i].path, " ");
			else if (glob[i].path != NULL && *str != NULL)
			{
				*str = ft_free_join(*str, glob[i].path, 'L');
				*str = ft_free_join(*str, " ", 'L');
			}
		}
		i++;
	}
}

void			freeall(char *pwd, char **res, char **s_tab, t_glob *glob)
{
	int			i;

	if (glob != NULL)
	{
		i = 0;
		while (i < glob->len)
		{
			if (glob[i].path)
				free(glob[i].path);
			i++;
		}
		free(glob);
	}
	if (pwd != NULL)
		free(pwd);
	if (res != NULL)
		ft_free_tab(res);
	if (s_tab != NULL)
		ft_free_tab(s_tab);
}

char			*ft_add_b_slash(char *file)
{
	char		escape_tab[25];
	char		*new;
	int			j;
	int			k;
	int			i;

	if ((new = malloc(sizeof(char) * (ft_strlen(file) * 2) + 1)) == NULL)
		return (NULL);
	ft_init_escape_tab(escape_tab);
	j = -1;
	k = -1;
	while (file[++j])
	{
		i = -1;
		while (escape_tab[++i])
			if (file[j] == escape_tab[i + 1])
				new[++k] = '\\';
		new[++k] = file[j];
	}
	new[++k] = '\0';
	return (new);
}

char			**ft_add_slash(char *path, char c)
{
	int			i;
	int			j;
	int			len;
	char		**s_tab;
	char		**slash_tmp;

	len = (path[0] == '/') ? ft_count_word(path, '/') + 1 :
		ft_count_word(path, '/');
	if ((s_tab = (char **)malloc(sizeof(char *) * (len + 1))) == NULL)
		return (NULL);
	slash_tmp = ft_strsplit(path, '/');
	i = -1;
	j = -1;
	if (path[0] == '/')
		s_tab[++j] = ft_strdup("/");
	while (slash_tmp[++i])
	{
		s_tab[++j] = ((c != '/' && i == len - 1) ||
				(path[0] == '/' && i == len - 2 && c != '/')) ?
			ft_strdup(slash_tmp[i]) : ft_strjoin(slash_tmp[i], "/");
	}
	s_tab[++j] = NULL;
	ft_free_tab(slash_tmp);
	return (s_tab);
}
