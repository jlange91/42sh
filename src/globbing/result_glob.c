/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result_glob.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 18:20:38 by stvalett          #+#    #+#             */
/*   Updated: 2018/01/19 18:33:51 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/globbing.h"

static	char	*ft_goodpath(char **s_tab, int *ret)
{
	char		*new;
	int			i;

	i = 0;
	new = NULL;
	if (s_tab)
	{
		while (s_tab[i])
			if (!ft_glob_here(s_tab[i]))
				i++;
			else
				break ;
		new = ft_strdup(s_tab[0]);
		*ret = i;
		i = 1;
		while (s_tab[i] && i != *ret)
		{
			new = ft_free_join(new, s_tab[i], 'L');
			i++;
		}
	}
	return (new);
}

static	t_glob	ft_fillglob2(char *file, int ret, char **s_tab)
{
	t_glob		glob;
	int			k;
	struct stat	info;

	glob.path = NULL;
	ft_memset(&info, 0, sizeof(info));
	stat(file, &info);
	if (S_ISDIR(info.st_mode))
		glob.path = ft_strjoin(file, "/");
	else
		glob.path = ft_strdup(file);
	if (ret == 99)
		return (glob);
	k = ret;
	while (s_tab[k])
	{
		glob.path = ft_free_join(glob.path, s_tab[k], 'L');
		k++;
	}
	return (glob);
}

static	t_glob	*ft_addopenglobsplit(char **res, char **s_tab, int ret)
{
	t_glob		*new;
	int			i;

	if ((new = (t_glob *)malloc(sizeof(t_glob) * ft_count_dtab(res))) == NULL)
		exit(0);
	if (s_tab[++ret] == NULL)
		ret = 99;
	i = -1;
	while (res[++i])
		new[i] = ft_fillglob2(res[i], ret, s_tab);
	new->len = ft_count_dtab(res);
	return (new);
}

static	void	ft_addopenglob(t_glob *glob, int star, char **str)
{
	t_glob		*new;
	char		**s_tab;
	char		**res;
	char		*path;
	int			ret;

	if (!glob->path)
		return ;
	ret = 0;
	s_tab = ft_add_slash(glob->path, glob->path[ft_strlen(glob->path) - 1]);
	path = ft_goodpath(s_tab, &ret);
	if ((res = ft_open(path, s_tab[ret], star, 0)) != NULL
			&& ft_count_dtab(res) > 0)
	{
		new = ft_addopenglobsplit(res, s_tab, ret);
		ret = -1;
		while (++ret < new->len)
			ft_addopenglob(&new[ret], star, str);
		ft_save_word(&new[0], str, new->len);
		freeall(path, res, s_tab, new);
		return ;
	}
	freeall(path, res, s_tab, NULL);
}

char			*ft_resglob(t_glob *glob, int star, char **str)
{
	int			i;

	i = 0;
	while (i < glob->len)
	{
		ft_addopenglob(&glob[i], star, str);
		i++;
	}
	return (*str);
}
