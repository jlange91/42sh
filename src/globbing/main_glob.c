/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <stvalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 19:11:16 by stvalett42        #+#    #+#             */
/*   Updated: 2017/12/19 15:14:59 by adebrito         ###   ########.fr       */
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
		{
			ft_freeall_glob(NULL, res, s_tab, glob);
			return (NULL);
		}
	}
	else
		glob[0] = ft_fillglob(NULL, word);
	ft_freeall_glob(NULL, res, s_tab, NULL);
	glob->len = len;
	return (glob);
}

static inline char		*ft_braces_glob(char *word)
{
	char	**tab;
	char	*tmp;
	char	*str;
	int		i;

	str = NULL;
	tmp = ft_strtrim2(word, '{', '}');
	tab = ft_strsplit(tmp, ',');
	free(tmp);
	i = -1;
	while (tab[++i])
	{
		if (str == NULL)
			str = ft_glob(tab[i]);
		else if ((tmp = ft_glob(tab[i])) != NULL)
		{
			str = ft_free_join(str, tmp, 'B');
			str = ft_free_join(str, " ", 'L');
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
		return (ft_braces_glob(word));
	if (word && ft_glob_here(word) && !ft_syntax_braces(word) &&
			ft_syntax_bracket(word))
	{
		star = ft_only_star(word);
		glob = ft_firstinitglob(word, star);
		if (glob != NULL)
		{
			ft_resGlob(&glob[0], star, &str);
			if ((str == NULL && glob->res == NULL) || (str == NULL && star))
				ft_save_word(&glob[0], &str, glob->len);
			ft_freeall_glob(NULL, NULL, NULL, &glob[0]);
			return (str);
		}
	}
	return (NULL);
}
