#include "../../inc/sh21.h"

int     ft_count_av1(char *line);
int     ft_count_av2(char *line, char **av);
int     ft_char_escape(char c);
void    ft_charcat(char *str, char c);

static int		ft_backslash(char *line, int *i, char *av)
{
    int ret;

    ret = 0;
	if (line[*i] != '\\')
		ret = 0;
    else if (!ft_char_escape(line[*i + 1]))
        ret = 1;
    else
    {
        ft_charcat(av, line[*i + 1]);        
        ret = 2;
    }
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

static void     ft_skip_quote(char *line, int *i, char *av)
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
            if (line[*i] == '\\' && line[*i + 1] != '\'' && line[*i + 1] == c)
            {
                ft_charcat(av, line[*i + 1]);
                *i += 2;
            }
            if (line[*i] == c)
            {
                *i += 1;
                return ;
            }
            ft_charcat(av, line[*i]);            
            *i += 1;
        }
    }
}

static void    ft_skip_word(char *line, int *i, char *av)
{
    while (line[*i] != ' ' && line[*i] != '\'' && line[*i] != '"' && line[*i])
    {
        if (ft_backslash(line, i, av) == 0)
        {
            ft_charcat(av, line[*i]);
            *i += 1;
        }
    }
}

void     ft_fill(char *line, char **av)
{
    int i;
    int count;
    int space;

    count = 0;
    i = 0;
    space = 0;
    while (line[i])
    {
        ft_skip_word(line, &i, av[count]);
        ft_skip_quote(line, &i, av[count]);
        space = ft_skip_useless(&line[i]);
        if (space > 0 || !line[i])
        {
            i += space;
            count++;
        }
    }
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
    ret = 0;
    while (av[ret])
    {
        av[ret][0] = '\0';
        ret++;
    }
    ret = 0;
    ft_fill(line, av);
    write(1, "\n", 1);
    while (av[ret])
    {
        printf("[%s]\n", av[ret]);
        ret++;
    }
    return (NULL);
}