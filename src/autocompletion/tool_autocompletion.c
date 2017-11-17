#include "../../inc/autocompletion.h"

void    ft_fill_back_autocompl(t_auto *autocompl, char *file, int index)
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
    new->prev = autocompl->end;
    if (autocompl->end)
        autocompl->end->next = new;
    else
        autocompl->begin = new;
    autocompl->end = new;
}

char	*ft_to_str(t_termc *shell)
{
    char	*str;
    int		i;
    t_lineterm  *tmp;

    if ((str = (char *)malloc(sizeof(*str) * (ft_count_dlnk(shell) + 1)))
            == NULL)
    {
        ft_putendl_fd("Error malloc", 2);
        return (NULL);
    }
    tmp = shell->line->begin;
    i = 0;
    if (tmp->next)
        tmp = ft_dont_get_prompt(tmp);
    while (tmp)
    {
        str[i] = tmp->c;
        i++;
        tmp = tmp->next;
    }
    str[i] = '\0';
    return (str);
}

char	*ft_before_antislash(char *str, int ret)
{
    char	*tmp;
    int		i;

    i = 0;
    if ((tmp = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1))) == NULL)
    {
        ft_putendl_fd("Error malloc", 2);
        return (NULL);
    }
    while (str[i])
    {
        if (i == ret)
            break;
        tmp[i] = str[i];
        i++;
    }
    tmp[i] = '\0';
    return (tmp);
}

char    *ft_after_antislash_bis(char *str, int limit)
{
    char	*tmp;
    int     j;

    j = 0;
    if ((tmp = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1))) == NULL)
    {
        ft_putendl_fd("Error malloc", 2);
        return (NULL);
    }
    while (str[limit])
        tmp[j++] = str[limit++];
    tmp[j] = '\0';
    return (tmp);
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
    return (ft_after_antislash_bis(str, i));
}
