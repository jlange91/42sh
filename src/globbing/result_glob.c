#include "../../inc/globbing.h"
#include "../../inc/autocompletion.h"
#include "../../inc/env_term.h"
#include "../../inc/built_in.h"

static inline int  ft_count_file(char *str)
{
	int             count;
	DIR             *path;
	struct dirent   *file;

	count = 0;
	if ((path = opendir(str)) != NULL)
	{
		while ((file = readdir(path)) != NULL)
			count++;
		closedir(path);
	}
	return (count);
}

static char    **ft_opendir_current(t_env *env)
{
	int             i;
	char            **tmp_tab;
	char            *pwd;
	DIR             *path;
	struct dirent   *file;

	i = -1;
	tmp_tab = NULL;
	pwd = find_var("PWD", env);
	if ((path = opendir(pwd)) != NULL)
	{
		if ((tmp_tab = (char **)malloc(sizeof(char *) *
						(ft_count_file(pwd) + 1))) == NULL)
		{
			ft_putendl_fd("Error malloc", 2);
			return (NULL);
		}
		while ((file = readdir(path)) != NULL)
			if (file->d_name[0] != '.')
				tmp_tab[++i] = ft_strdup(file->d_name);
		tmp_tab[++i] = NULL;
		closedir(path);
	}
	return (tmp_tab);
}

static char    **ft_opendir_choice(char *pwd)
{
	int             i;
	char            **tmp_tab;
	DIR             *path;
	struct dirent   *file;

	i = -1;
	tmp_tab = NULL;
	if ((path = opendir(pwd)) != NULL)
	{
		if ((tmp_tab = (char **)malloc(sizeof(char *) *
						(ft_count_file(pwd) + 1))) == NULL)
		{
			ft_putendl_fd("Error malloc", 2);
			return (NULL);
		}
		while ((file = readdir(path)) != NULL)
			if (file->d_name[0] != '.')
				tmp_tab[++i] = ft_strdup(file->d_name);
		tmp_tab[++i] = NULL;
		closedir(path);
	}
	return (tmp_tab);
}

static char        *ft_result_final(char *pattern, char *tmp_tab, char *before)
{
	int		index;

	index = 0;
	index = ft_strlen(before) - 1;
	if (index == -1)
		index = 0;
	if (pattern[index] == '/')
		index++;
	if (ft_match(&pattern[index], tmp_tab))
		return (tmp_tab);
	return (NULL);
}

char        **ft_result(t_env *env, t_glob *g, char **str_tab)
{
	if ((g->new_tab = (char **)malloc(sizeof(char *) * (ft_count_dtab(str_tab) + 1 * 50))) == NULL)				// not good malloc, too big
		return (NULL);
	g->i = -1;
	g->j = -1;
	g->ret = 0;
	while (str_tab[++(g->i)])
		if (ft_glob_here(str_tab[g->i]))
		{
			g->after = ft_after_antislash(str_tab[g->i], &g->ret);
			g->before = ft_before_antislash(str_tab[g->i], g->ret);
			g->tmp_tab = (g->after == NULL && g->before) ?
				ft_opendir_current(env) : ft_opendir_choice(g->before);
			g->k = -1;
			while (g->tmp_tab[++(g->k)])
				if ((g->tmp = ft_result_final(str_tab[g->i],
								g->tmp_tab[g->k], g->before)) != NULL)
					g->new_tab[++(g->j)] = ft_strdup(g->tmp);
			free(g->before);
			free(g->after);
			ft_free_tab(g->tmp_tab);
		}
	g->new_tab[++(g->j)] = NULL;
	if (g->j == 0)
	{
		ft_free_tab(g->new_tab);
		g->new_tab = NULL;
	}
	return (g->new_tab);
}
