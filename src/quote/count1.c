#include "../../inc/sh21.h"

int     ft_char_escape(char c);

// char	*ft_strndup(const char *s1, int size)
// {
// 	char *str;

// 	if ((str = (char *)malloc(sizeof(*str) * (size + 1))) == NULL)
//         return (NULL);
// 	ft_strncpy(str, s1, size);
// 	return (str);
// }

static int		ft_backslash(char *line, int *i)
{
    int ret;

    ret = 0;
	if (line[*i] != '\\')
		ret = 0;
	else if (!ft_char_escape(line[*i + 1]))
        ret = 1;
    else
        ret = 2;
    *i += (ret > 0) ? ret : 0;
    return (ret);
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
        *i += 1;
        while (line[*i])
        {
            *i += (line[*i] == '\\' && line[*i + 1] == '\'' && line[*i + 1] == c) ? 2 : 0;            
            if (line[*i] == c)
            {
                *i += 1;
                return ;
            }
            *i += 1;
        }
    }
}

static void    ft_skip_word(char *line, int *i)
{
    while (line[*i] != ' ' && line[*i] != '\'' && line[*i] != '"' && line[*i])
    {
        if (ft_backslash(line, i) == 0)
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