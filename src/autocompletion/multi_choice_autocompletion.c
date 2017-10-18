#include "../../inc/autocompletion.h"

int		ft_dir_or_not(char *line)
{
	struct stat info;

	ft_memset(&info, 0, sizeof(info));
	stat(line, &info);
	if (S_ISDIR(info.st_mode))
		return (1);
	return (0);
}

int		ft_dir_or_not2(char *line)
{
	struct stat info;
	char		**tab_tmp;
	int			index;
	int			flag;

	flag = 0;
	ft_memset(&info, 0, sizeof(info));
	tab_tmp = ft_strsplit2(line);
	index = ft_count_dtab(tab_tmp) - 1;
	stat(tab_tmp[index], &info);
	if (S_ISDIR(info.st_mode))
		flag = 1;
	ft_free_tab(tab_tmp);
	return (flag);
}

static t_auto  *ft_sort_list(t_shell *shell, char *after, int ret, int len)
{
	int         i;
	char		*str;
	t_auto      *tmp;
	t_autocompl *begin;
    t_autocompl *begin_tmp;

	tmp = NULL;
	if ((tmp = (t_auto *)malloc(sizeof(*tmp))) == NULL)
	{
		ft_putendl_fd("Error malloc", 2);
		return (NULL);
	}
	tmp->begin = NULL;
	tmp->end = NULL;
	tmp->current = NULL;
	begin = shell->autocompl->begin;
	i = 0;
	if (begin)
	{
		while (begin)
		{
			if (ft_strncmp(after, begin->data, ft_strlen(after)) == 0)
			{
				char	*str_tmp;

				str = ft_before_antislash(shell->autocompl->str, len);
				str_tmp = ft_strjoin(str, begin->data);
				if (ft_dir_or_not2(str_tmp) || ft_dir_or_not(begin->data))
					ft_fill_back_autocompl(tmp, begin->data, ++i);
				free(str);
				free(str_tmp);
			}
			begin = begin->next;
		}
        if (ret)
        {
            begin = shell->autocompl_binary->begin;
            while (begin)
            {
			    if (ft_strncmp(after, begin->data, ft_strlen(after)) == 0)
                {
                    int test;

                    test = 0;
                    begin_tmp = tmp->begin;
                    while (begin_tmp)
                    {
                        if (ft_strcmp(begin_tmp->data, begin->data) == 0)
                        {
                            test = 1;
                            break;
                        }
                        begin_tmp = begin_tmp->next;
                    }
                    if (!test)
				        ft_fill_back_autocompl(tmp, begin->data, ++i);
                }
			    begin = begin->next;
            }
        }
	}
	return (tmp);
}

static int  ft_try_fill(t_shell *shell, char *after, int *flag, int ret, int len)
{
	int         i;
	t_auto      *tmp;

	tmp = NULL;
	if ((tmp = ft_sort_list(shell, after, ret, len)) != NULL)
	{
		ft_free_autocompletion(&shell->autocompl);
		i = 0;
		*flag = (ft_count(tmp) < 1) ? 0 : 1;
		while (tmp->begin)
		{
			ft_fill_back_autocompl(shell->autocompl, tmp->begin->data, i++);
			tmp->begin = tmp->begin->next;
		}
		shell->autocompl->current = shell->autocompl->begin;
		ft_free_autocompletion(&tmp);
		free(tmp);
	}
	return (0);
}

int    ft_fill_same_word(t_shell *shell, t_env *env)
{
	char        *after;
	char		*tmp;
	char        *tmp_line;
	int         ret;
	int         flag;

	ret = 0;
	after = NULL;
	flag = 0;
	tmp = NULL;
	if (shell->autocompl->str != NULL && shell->autocompl->begin != NULL)
	{
		if (ft_dir_or_not(shell->autocompl->str))
		{
			tmp = ft_strjoin(shell->autocompl->str, "/");
			tmp_line = ft_strdup(tmp);
			free(tmp);
		}
		else
			tmp_line = ft_strdup(shell->autocompl->str);
		if ((after = ft_after_antislash(tmp_line, &ret)) != NULL)
		{
			ft_try_fill(shell, after, &flag, 0, ret);
			free(after);
		}
		else
		{
            if (shell->multiauto_active == 1)
			    ft_try_fill(shell, tmp_line, &flag, 0, 0);
            else
			    ft_try_fill(shell, tmp_line, &flag, 1, 0);
			ft_init_autocompl(shell, tmp_line, env);
		}
		free(tmp_line);
	}
	return (flag);
}
