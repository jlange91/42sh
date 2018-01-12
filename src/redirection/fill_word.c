#include "../../inc/quote.h"

static int		backslash_word(char *line, char *word)
{
	if (line[0] != '\\')
		return (0);
	if (line[1] == '\n')
		return (2);
	else
	{
		ft_charcat(word, line[1]);
		return (1);
	}
}

static void    skip_word(char *line, int *i, char *word)
{
	int ret;

	ret = 0;
	while (line[*i] != ' ' && line[*i] != '\t' && line[*i] != '\n'
			&& line[*i] != '\'' && line[*i] != '"' && line[*i] != '>' &&
			line[*i] != '<' && line[*i])
	{
		ret = backslash_word(&line[*i], word);
		if (ret > 0)
			*i += 1;
		else
			ft_charcat(word, line[*i]);
		*i += 1;
	}
}

static int		backslash_quote(char *line, char c, char *word)
{
	if (line[0] != '\\' || c == '\'')
		return (0);
	if (line[1] == '\n')
		return (2);
	else if (line[1] == '$' || line[1] == '`' ||
			line[1] == '"' || line[1] == '\\')
	{
		ft_charcat(word, line[1]);
		return (1);
	}
	else
		return (0);
}

static void     skip_quote(char *line, int *i, char *word)
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
			ret = backslash_quote(&line[*i], c, word);
			if (ret > 0)
				*i += 1;
			else
				ft_charcat(word, line[*i]);
			*i += 1;
		}
		*i += (line[*i] == c) ? 1 : 0;
	}
}

void     ft_fill_word(char *line, char *word)
{
	int i;
	int j;
	int space;

	i = 0;
	j = 0;
	space = 0;
	while (line[i])
	{
		i += ft_skip_useless(&line[i]);
		skip_word(line, &i, word);
		skip_quote(line, &i, word);
		space = ft_skip_useless(&line[i]);
		if (space > 0 || !line[i] || line[i] == '>' || line[i] == '<')
		{
			while (j < i)
			{
				line[j] = ' ';
				j++;
			}
			return ;
		}
	}
}
