#include "../../inc/sh21.h"

int     ft_char_escape(char c);

static int		ft_backslash(char *line, int *i, int *count)
{
    int ret;

    ret = 0;
	if (line[*i] != '\\')
		ret = 0;
	else if (!ft_char_escape(line[*i + 1]))
        ret = 1;
    else
        ret = 2;
    *count += (ret == 2) ? 1 : 0;
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

static void     ft_skip_quote(char *line, int *i, int *count)
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
            *count += (line[*i] == '\\' && line[*i + 1] != '\'' && line[*i + 1] == c) ? 1 : 0;            
            *i += (line[*i] == '\\' && line[*i + 1] != '\'' && line[*i + 1] == c) ? 2 : 0;
            if (line[*i] == c)
            {
                *i += 1;
                return ;
            }
            *count += 1;
            *i += 1;
        }
    }
}

static void    ft_skip_word(char *line, int *i, int *count)
{
    while (line[*i] != ' ' && line[*i] != '\'' && line[*i] != '"' && line[*i])
    {
        if (ft_backslash(line, i, count) == 0)
        {
            *i += 1;
            *count += 1;
        }
    }
}

int     ft_count_av2(char *line, char **av)
{
    int i;
    int j;
    int count;
    int space;

    count = 0;
    i = 0;
    j = 0;
    space = 0;
    while (line[i])
    {
        ft_skip_word(line, &i, &count);
        ft_skip_quote(line, &i, &count);
        space = ft_skip_useless(&line[i]);
        if (space > 0 || !line[i])
        {
            i += space;
            av[j] = (char*)malloc(sizeof(char) * (count + 1));
            ft_putnbr(count);
            write(1, " ; ", 3);
            j++;
            count = 0;
        }
    }
    return (count);
}