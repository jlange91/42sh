/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <vmartins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 19:11:16 by vmartins42        #+#    #+#             */
/*   Updated: 2018/03/06 16:39:33 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/globbing.h"

static inline t_glob	ft_fillglob(char *file, char *word)
{
	t_glob		glob;
	int			k;
	char		**s_tab;
	struct stat info;

	s_tab = ft_add_slash(word, word[ft_strlen(word) - 1]);
	ft_memset(&info, 0, sizeof(info));
	stat(file, &info);
	if (s_tab != NULL && ft_glob_here(s_tab[0]))
		glob.path = (S_ISDIR(info.st_mode)) ? ft_strjoin(file, "/") :
			ft_strdup(file);
	else if (s_tab[1] != NULL)
		glob.path = ft_strdup(s_tab[0]);
	k = 0;
	while (s_tab[++k])
		glob.path = ft_free_join(glob.path, s_tab[k], 'L');
	ft_free_tab(s_tab);
	return (glob);
}

static inline int		ft_initvar(char ***res, char ***s_tab, char *wo, int st)
{
	int len;

	len = 0;
	*s_tab = ft_add_slash(wo, wo[ft_strlen(wo) - 1]);
	*res = (*s_tab != NULL && !ft_glob_here(*s_tab[0])) ? NULL :
		ft_open(".", *s_tab[0], st, 1);
	len = (*res == NULL) ? 1 : ft_count_dtab(*res);
	return (len);
}

static inline t_glob	*ft_firstinitglob(char *word, int star)
{
	t_glob	*glob;
	char	**s_tab;
	char	**res;
	int		i;
	int		len;

	len = ft_initvar(&res, &s_tab, word, star);
	if ((glob = (t_glob *)malloc(sizeof(t_glob) * (len))) == NULL)
		return (NULL);
	if (len != 1 || res != NULL)
	{
		i = -1;
		while (res[++i])
			glob[i] = ft_fillglob(res[i], word);
		if (i == 0)
			return (ft_free_or_not(res, s_tab, glob, len));
	}
	else
		glob[0] = ft_fillglob(NULL, word);
	freeall(NULL, res, s_tab, NULL);
	glob->len = len;
	return (glob);
}

static inline char		*ft_braces_glob(char *word, int i, char *str)
{
	char	**tab;
	char	*tmp;

	tmp = ft_strtrim2(word, '{', '}');
	tab = ft_strsplit(tmp, ',');
	free(tmp);
	while (tab[++i])
	{
		if ((tmp = ft_glob(tab[i])) != NULL)
		{
			if (str == NULL)
				str = tmp;
			else
			{
				str = ft_free_join(str, tmp, 'B');
				str = ft_free_join(str, " ", 'L');
			}
		}
		else
			break ;
	}
	(i != ft_count_dtab(tab)) ? ft_strdel(&str) : str;
	ft_free_tab(tab);
	return (str);
}

char					*ft_glob(char *word)
{
	int		star;
	t_glob	*glob;
	char	*str;

	str = NULL;
	if (word && ft_glob_here(word) && ft_syntax_braces(word))
		return (ft_braces_glob(word, -1, NULL));
	if (word && ft_glob_here(word) && !ft_syntax_braces(word) &&
			ft_syntax_bracket(word))
	{
		star = ft_only_star(word);
		glob = ft_firstinitglob(word, star);
		if (glob != NULL)
		{
			ft_resglob(&glob[0], star, &str);
			if ((str == NULL && glob->res == NULL) || (str == NULL && star))
				ft_save_word(&glob[0], &str, glob->len);
			freeall(NULL, NULL, NULL, &glob[0]);
			return (str);
		}
	}
	return (NULL);
}
