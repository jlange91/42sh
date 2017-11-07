#include "../../inc/quote.h"

static int		backslash_word(char *line, char *av)
{
	if (line[0] != '\\')
		return (0);
	if (line[1] == '\n')
        return (2);
    else
    {
        ft_charcat(av, line[1]);
        return (1);
    }
}

static void    skip_word(char *line, int *i, char *av)
{
    int ret;

    ret = 0;
    while (line[*i] != ' ' && line[*i] != '\t' && line[*i] != '\n'
    && line[*i] != '\'' && line[*i] != '"' && line[*i])
    {
        ret = backslash_word(&line[*i], av);
        if (ret > 0)
            *i += 1;
        else
            ft_charcat(av, line[*i]);
        *i += 1;
    }
}

static int		backslash_quote(char *line, char c, char *av)
{
	if (line[0] != '\\' || c == '\'')
        return (0);
    if (line[1] == '\n')
        return (2);
    else if (line[1] == '$' || line[1] == '`' ||
    line[1] == '"' || line[1] == '\\')
    {
        ft_charcat(av, line[1]);
        return (1);
    }
    else
        return (0);
}

static void     skip_quote(char *line, int *i, char *av)
{
    int save;
    char c;
    int ret;
    
    save = *i;
    if (line[*i] == '\'' || line[*i] == '"')
    {
        c = line[*i];
        *i += 1;
        while (line[*i] && line[*i] != c)
        {
            ret = backslash_quote(&line[*i], c, av);
            if (ret > 0)
                *i += 1;
            else
                ft_charcat(av, line[*i]);
            *i += 1;
        }
        *i += (line[*i] == c) ? 1 : 0;
    }
}

void     ft_fill(char *line, char **av)
{
    int i;
    int j;
    int space;

    i = 0;
    j = 0;
    space = 0;
    while (line[i])
    {
        skip_word(line, &i, av[j]);
        skip_quote(line, &i, av[j]);
        space = ft_skip_useless(&line[i]);
        if (space > 0 || !line[i])
        {
            i += space;
            j++;
        }
    }
}
