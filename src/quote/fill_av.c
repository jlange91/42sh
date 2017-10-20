#include "../../inc/sh21.h"

int     ft_count_av1(char *line);

static int		ft_echap_char(char *line, char c, int *i, int *count)
{
    int ret;

    ret = 0;
	if (*line != '\\')
		ret = 0;
	else if (!line[1])
		ret = -1;
	else
        ret = (c != '\'') ? 1 : 0;
    *count += (ret == 1) ? 1 : 0;
    *i += (ret == 1) ? 2 : 0;
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
            if (ft_echap_char(&line[*i], c, i, count) == 0)
            {
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
}

static void    ft_skip_word(char *line, int *i, int *count)
{
    while (line[*i] != ' ' && line[*i] != '"' && line[*i])
    {
        if (ft_echap_char(&line[*i], 0, i, count) == 0)
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