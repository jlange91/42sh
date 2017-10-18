#include "../../inc/env_term.h"

static t_env           *init_lnk_env(char *str, int i)
{
    t_env   *env_c;

    if ((env_c = (t_env *)malloc(sizeof(t_env))) == NULL)
    {
        ft_putendl_fd("Error malloc() struct env", 2);
        return (NULL);
    }
    env_c->line_str = NULL;
    env_c->line_env = ft_strdup(str);
    env_c->index = i;
    env_c->getenv_path = NULL;
    env_c->next = NULL;
    return (env_c);
}

void    ft_cpy_env(t_env **env_c, char *str, int i)
{
    t_env   *tmp;

    tmp = *env_c;
    if (tmp)
    {
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = init_lnk_env(str, i);
    }
    else
        *env_c = init_lnk_env(str, i);
}

static	char	*ft_getpath_bis(char *s1, char *s2)
{
	char	*tmp;
	char	*path;

	path = ft_strdup(s1);
	if ((tmp = (char *)malloc(sizeof(char) * (ft_strlen(path) + 1))) == NULL)
		return (NULL);
	ft_strcpy(tmp, path);
	free(path);
	path = ft_strjoin(tmp, "=");
	free(tmp);
	if ((tmp = (char *)malloc(sizeof(char) * (ft_strlen(path) + 1))) == NULL)
		return (NULL);
	ft_strcpy(tmp, path);
	free(path);
	if (s2 != NULL)
	{
		path = ft_strjoin(tmp, s2);
		free(tmp);
	}
	return (path);
}

char			*ft_getpath(const char *line, const char *value)
{
	char	*path;
	char	*s1;
	char	*s2;
	int		flag;

	flag = 0;
	s1 = ft_strtrim2((char *)line, '"', '\'');
	s2 = NULL;
	if (value != NULL)
	{
		s2 = ft_strtrim2((char *)value, '"', '\'');
		flag = 1;
	}
	path = ft_getpath_bis(s1, s2);
	ft_free_str(s1, s2, flag);
	return (path);
}
