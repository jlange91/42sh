#include "../../inc/sh21.h"

int     ft_count_av1(char *line);
int     ft_count_av2(char *line, char **av);

char **ft_fill_av(char *line)
{
    char **av;
    int ret;

    write(1, "\n" , 1);
    ret = ft_count_av1(line);
    if (!(av = (char**)malloc(sizeof(char*) * (ret + 1))))
        return (NULL);
    av[ret] = NULL;
    write(1, "\n", 1);
    ft_count_av2(line , av);
    return (NULL);
}