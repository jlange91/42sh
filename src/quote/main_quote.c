#include "../../inc/quote.h"

char **ft_fill_av(char *line)
{
    char **av;
    int ret;

    av = NULL;
    ret = ft_count_av1(line);
    if (!(av = (char**)malloc(sizeof(char*) * (ret + 1))))
        return (NULL);
    av[ret] = NULL;
    ft_count_av2(line , av);
    ret = 0;
    while (av[ret])
    {
        av[ret][0] = '\0';
        ret++;
    }
    ft_fill(line, av);
    return (av);
}
