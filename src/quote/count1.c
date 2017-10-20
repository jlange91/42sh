#include "../../inc/sh21.h"

// char	*ft_strndup(const char *s1, int size)
// {
// 	char *str;

// 	if ((str = (char *)malloc(sizeof(*str) * (size + 1))) == NULL)
//         return (NULL);
// 	ft_strncpy(str, s1, size);
// 	return (str);
// }

static int		ft_echap_char(char *line, char c)
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

static int		ft_skip_useless(char *line)
{
	int i;

    i = 0;
    while (line[i])
    {
        if (line[i] != ' ')
            break ;
	    while (line[i] == ' ')
            i++;
        if ((line[i] == '\'' || line[i] == '"') && line[i] == line[i + 1])
            i += 2;
    }
	return (i);
}

static void     ft_skip_quote(char *line, int *i)
{
    int save;
    char c;
    
    save = *i;
    if (line[*i] == '\'' || line[*i] == '"')
    {
        c = line[*i];
        while (line[*i])
        {
            *i += 1;
            *i += ft_echap_char(&line[*i], c);
            if (line[*i] == c)
            {
                *i += 1;
                return ;
            }
        }
    }
}

static void    ft_skip_word(char *line, int *i)
{
    while (line[*i] != ' ' && line[*i] != '\'' && line[*i] != '"' && line[*i])
    {
        *i += ft_echap_char(&line[*i], 0);
        *i += 1;
    }
}

int     ft_count_av1(char *line)
{
    int i;
    int count;
    int space;

    count = 0;
    i = 0;
    space = 0;
    while (line[i])
    {
        ft_skip_word(line, &i);
        ft_skip_quote(line, &i);
        space = ft_skip_useless(&line[i]);
        if (space > 0 || !line[i])
        {
            i += space;
            count++;
        }
    }
    return (count);
}