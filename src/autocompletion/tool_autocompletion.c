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
    new->index = index;
    new->next = NULL;
    new->prev = autoc->end;
    if (autoc->end)
        autoc->end->next = new;
    else
        autoc->begin = new;
    autoc->end = new;
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
