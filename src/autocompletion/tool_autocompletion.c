#include "../../inc/autocompletion.h"

void    ft_fill_back_autocompl(t_auto *autoc, char *file, int index)
{
    t_autocompl *new;

    new = NULL;
    if ((new = (t_autocompl *)malloc(sizeof(*new))) == NULL)
    {
        ft_putendl_fd("Error malloc", 2);
        exit(0);
    }
    new->data = ft_strdup(file);
    new->pos = 0;
    new->last = 0;
    new->index = index;
    new->next = NULL;
    new->prev = autoc->end;
    if (autoc->end)
        autoc->end->next = new;
    else
        autoc->begin = new;
    autoc->end = new;
}

char	*ft_to_str(t_termc *tsh)
{
    char	*str;
    int		i;
    t_lineterm  *tmp;

    if ((str = (char *)malloc(sizeof(*str) * (ft_count_dlnk(tsh) + 1)))
            == NULL)
    {
        ft_putendl_fd("Error malloc", 2);
        return (NULL);
    }
    tmp = tsh->line->begin;
    i = 0;
    if (tmp->next)
        tmp = ft_dontGetPrompt2(tmp);
    while (tmp)
    {
        str[i] = tmp->c;
        i++;
        tmp = tmp->next;
    }
    str[i] = '\0';
    return (str);
}

char	*ft_after_antislash(char *str, int *ret)
{
    char	*tmp;
    int		i;
    int     enter;

    i = 0;
    enter = 0;
    tmp = NULL;
    i = ft_strlen(str) - 1;
    while (str[i] && str[i] != '/' && str[i] != ' ')
    {
        if (i == 0)
            return (tmp);
        enter = 1;
        i--;
    }
    i++;
    *ret = i;
    if (!enter)
        return (tmp);
	tmp = ft_strdup(&str[i]);
	return (tmp);
}
