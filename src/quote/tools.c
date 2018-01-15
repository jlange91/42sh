#include "../../inc/quote.h"

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

void	ft_remove_space(char **str)
{
	char	*tmp;

	tmp = ft_strtrim(*str);
	free(*str);
	*str = ft_strdup(tmp);
	free(tmp);
}
