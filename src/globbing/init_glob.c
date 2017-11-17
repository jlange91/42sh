#include "../../inc/globbing.h"
#include "../../inc/autocompletion.h"

void			ft_print_glob(char **tmp)
{
	int i;

	i = -1;
	ft_putchar('\n');
	while (tmp[++i])
		ft_putendl(tmp[i]);
}

static char    *ft_add_space(char *line)
{
    char    *str;
    int     i;

    str = NULL;
    if ((str = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1))) == NULL)
    {
        ft_putendl_fd("Error malloc", 2);
        return (NULL);
    }
    i = 0;
    while (line[i])
    {
        if (line[i] == ';' || line[i] == '&' || line[i] == '|'
				|| line[i] == '{' || line[i] == '}' || line[i] == ',')
            str[i] = ' ';
        else
            str[i] = line[i];
        i++;
    }
    str[i] = '\0';
    return (str);
}

static t_glob  *ft_init_glob(char *line)
{
    t_glob *new;

    new = NULL;
    if ((new = (t_glob *)malloc(sizeof(t_glob))) == NULL)
    {
        ft_putendl_fd("Error malloc", 2);
        return (NULL);
    }
    new->line = ft_add_space(line);
    new->tab_str = NULL;
	new->tmp = NULL;
	new->new_tab = NULL;
    return (new);
}

int    ft_parse_glob(char *line, t_glob **glob, char **env)
{
    char    **str_tab;
	int		flag;

	flag = 0;
    if (line && ft_strlen(line) == 0)
        return (flag);
    else if (!(ft_glob_here(line)))
        return (flag);
    else
    {
        str_tab = NULL;
        *glob = ft_init_glob(line);
        if ((str_tab = ft_strsplit2((*glob)->line)) != NULL)
        {
            if (ft_get_glob(glob, str_tab, env))
				flag = 1;
            ft_free_tab(str_tab);
        }
		free((*glob)->line);
    }
	return (flag);
}
