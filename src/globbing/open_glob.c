/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_glob.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 18:15:15 by stvalett          #+#    #+#             */
/*   Updated: 2018/01/19 18:20:23 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/globbing.h"

static	int			ft_check_dot(char *file, char *pattern)
{
	if (pattern && pattern[0] == '.' && file && file[0] == '.')
	{
		if (ft_strlen(file) == 2 && file[0] == '.' && file[1] == '.')
			return (0);
		else if (ft_strlen(file) == 1 && file[0] == '.')
			return (0);
		else
			return (1);
	}
	else if (pattern && pattern[0] != '.' && file[0] == '.')
		return (0);
	return (1);
}

static	char		*ft_find_glob(char *pattern, char *file)
{
	char			*tmp_pattern;

	if (pattern[ft_strlen(pattern) - 1] == '/')
	{
		tmp_pattern = ft_strtrim2(pattern, '/', '/');
		if (ft_match(tmp_pattern, file))
		{
			free(tmp_pattern);
			return (file);
		}
		free(tmp_pattern);
	}
	if (ft_match(pattern, file))
		return (file);
	return (NULL);
}

static	char		**ft_fill_tab2(char *pat, int star, DIR *path)
{
	int				i;
	char			**tmp_tab;
	struct dirent	*file;
	struct stat		info;

	i = -1;
	tmp_tab = NULL;
	if ((tmp_tab = (char **)malloc(sizeof(char *) *
					(ft_count_opendir((".")) + 1))) == NULL)
		return (NULL);
	while ((file = readdir(path)) != NULL)
	{
		ft_memset(&info, 0, sizeof(info));
		stat(file->d_name, &info);
		if ((ft_find_glob(pat, file->d_name) || star)
				&& (pat[ft_strlen(pat) - 1] != '/' || S_ISDIR(info.st_mode))
				&& ft_check_dot(file->d_name, pat))
			tmp_tab[++i] = ft_strdup(file->d_name);
	}
	tmp_tab[++i] = NULL;
	return (tmp_tab);
}

static	char		**ft_fill_tab1(char *pwd, char *pat, int star, DIR *path)
{
	char			*tmp;
	char			**tmp_tab;
	struct dirent	*file;
	struct stat		info;
	int				i;

	i = -1;
	if (!(tmp_tab = malloc(sizeof(char *) * (ft_count_opendir(pwd) + 1))))
		return (NULL);
	while ((file = readdir(path)) != NULL)
	{
		ft_memset(&info, 0, sizeof(info));
		stat((tmp = ft_strjoin(pwd, file->d_name)), &info);
		free(tmp);
		if ((ft_find_glob(pat, file->d_name) || star)
				&& (pat[ft_strlen(pat) - 1] != '/' || S_ISDIR(info.st_mode))
				&& ft_check_dot(file->d_name, pat))
			tmp_tab[++i] = ft_free_join(pwd, ft_add_b_slash(file->d_name), 'R');
	}
	tmp_tab[++i] = NULL;
	return (tmp_tab);
}

char				**ft_open(char *pwd, char *pattern, int star, int flag)
{
	char			**tmp_tab;
	DIR				*path;

	tmp_tab = NULL;
	if (!pwd)
		return (tmp_tab);
	if ((path = opendir(pwd)) != NULL)
	{
		if (pattern != NULL)
			tmp_tab = (flag) ? ft_fill_tab2(pattern, star, path) :
				ft_fill_tab1(pwd, pattern, star, path);
		if (closedir(path) != 0)
			ft_putendl_fd("Error closedir()", 2);
	}
	return (tmp_tab);
}
