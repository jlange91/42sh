#include "../../inc/quote.h"

static int		backslash_word(char *line)
{
	if (line[0] != '\\')
        return (0);
    if (!line[1])
        return (-1);
	if (line[1] == '\n')
        return (2);
    else
        return (1);
}

static int    skip_word(char *line, int *i)
{
    int ret;

    ret = 0;
    while (line[*i] != ' ' && line[*i] != '\t' && line[*i] != '\n'
    && line[*i] != '\'' && line[*i] != '"' && line[*i] != '`' && line[*i])
    {
        ret = backslash_word(&line[*i]);
        if (ret < 0)
            return (ret);
        if (ret > 0)
            *i += 1;
        *i += 1;
    }
    return (0);
}

static int		backslash_quote(char *line, char c)
{
	if (line[0] != '\\' || c == '\'')
        return (0);
    if (line[1] == '\n')
        return (2);
    else if (line[1] == '$' || line[1] == '`' ||
    line[1] == '"' || line[1] == '\\' || line[1] == '\n')
        return (1);
    else
        return (0);
}

static int     skip_quote(char *line, int *i)
{
    int save;
    char c;
    int ret;

    save = *i;
    if (line[*i] == '\'' || line[*i] == '"' || line[*i] == '`')
    {
        c = line[*i];
        *i += 1;
        while (line[*i] && line[*i] != c)
        {
            ret = backslash_quote(&line[*i], c);
            if (ret > 0)
                *i += 1;
            *i += 1;
        }
        if (line[*i] == c)
            *i += 1;
        else
            return (ft_return(c));
    }
    return (0);
}

int			ft_check_quote(char *line)
{
    int i;
    int space;
    int ret;

    i = 0;
    space = 0;
    ret = 0;
    while (line[i])
    {
        i += ft_skip_useless(&line[i]);
        if (skip_word(line, &i) < 0)
            return (-4);
        ret = skip_quote(line, &i);
        if (ret < 0)
            return (ret);
        space = ft_skip_useless(&line[i]);
        if (space > 0 || !line[i])
            i += space;
    }
    return (0);
}
