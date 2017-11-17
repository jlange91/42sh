#include "../../inc/quote.h"

int		ft_skip_useless(char *line)
{
	int i;

    i = 0;
    while (line[i])
    {
        if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
            break ;
	    while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
            i++;
    }
	return (i);
}

int    ft_return(char c)
{
    if (c == '"')
        return (-1);
    else if (c == '\'')
        return (-2);
    else if (c == '`')
        return (-3);
    else
        return (0);
}