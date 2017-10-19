#include "../../inc/sh21.h"

// char	*ft_strndup(const char *s1, int size)
// {
// 	char *str;

// 	if ((str = (char *)malloc(sizeof(*str) * (size + 1))) == NULL)
//         return (NULL);
// 	ft_strncpy(str, s1, size);
// 	return (str);
// }

int		ft_echap_char(char *line, char c)
{
	if (*line != '\\')
		return (0);
	else if (!line[1])
		return (-1);
	else if (line[1] == '\\')
		return (2);
	else
		return (c != '\'') ? 2 : 0;
}

int		ft_nb_space(char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	return (i);
}

int     index_to_end_quote(char *line, int *i, char c)
{
    *i += 1;
    while (line[*i])
    {
        *i += ft_echap_char(&line[*i], c);
        if (line[*i] == c)
            return (1);
        *i += 1;
    }
    return (0);
}

int     ft_check_quote(char *line, int *i)
{
    if (line[*i] == '\'' || line[*i] == '"')
    {
        if (line[*i] == line[*i + 1])
        {
            *i += ft_nb_space(&line[*i + 2]) + 1;
            return (0);
        }
        if (index_to_end_quote(line, i, line[*i]) == 1)
            return (line[*i + 1] == ' ' || !line[*i + 1]) ? 1 : 0;
    }
    else if (line[*i] == ' ' || !line[*i + 1])
        return (1);
    return (0);
}

int     ft_count_av(char *line)
{
    int i;
    int count;

    count = 0;
    i = 0;
    while (line[i])
    {
        if (ft_check_quote(line, &i))
        {
            count++;
            i += ft_nb_space(&line[i + 1]);
        }
        i++;
    }
    return (count);

}

char **ft_fill_av(char *line)
{
    write(1, "\n" , 1);
    ft_putnbr(ft_count_av(line));
    return (NULL);
}