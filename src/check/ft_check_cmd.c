#include "../../inc/sh21.h"
#include "../../inc/quote.h"

static int		backslash_word(char *line)
{
	if (line[0] != '\\')
		return (0);
	if (line[1] == '\n')
		return (2);
	else
		return (1);
}

static int     check_token(char *line)
{
	int ret;

	ret = 0;
	ret = (line[0] == ';') ? 2 : ret;
	ret = (line[0] == '&' && line[1] == '&') ? 3 : ret;
	ret = (line[0] == '|') ? 5 : ret;
	ret = (ret == 5 && line[1] == '|') ? 4 : ret;
	return (ret);
}

static int      check_next_token(char *line)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	i += ft_skip_useless(line);
	ret = (line[i] == '\n' || line[i] == 0) ? 1 : ret;
	ret = (line[i] == ';') ? 2 : ret;
	ret = (line[i] == '|') ? 3 : ret;
	ret = (line[i] == '&') ? 4 : ret;
	ret = (line[i] == '&' && line[i + 1] == '&') ? 5 : ret;
	ret = (line[i] == '|' && line[i + 1] == '|') ? 6 : ret;
	return (ret);
}

static void      print_error(int token)
{
	write(2, "42sh: syntax error near unexpected token `", 42);
	if (token == 1)
		write(2, "\\n", 2);
	else if (token == 2)
		write(2, ";", 1);
	else if (token == 3)
		write(2, "|", 2);
	else if (token == 4)
		write(2, "&", 1);
	else if (token == 5)
		write(2, "&&", 2);
	else if (token == 6)
		write(2, "||", 2);
	write(2, "'\n", 2);
}

int	ft_check_cmd(t_shell *sh)
{
	int i;
	int op;
	int token;

	i = 0;
	while (sh->line[i])
	{
		i += ft_skip_quote(&sh->line[i]);
		i += ft_skip_dquote(&sh->line[i]);
		if ((op = check_token(&sh->line[i])))
		{
			token = check_next_token(&sh->line[i + ((op == 3 || op == 4) ? 2 : 1)]);
			if (token)
			{
				print_error(token);
				return (1);
			}
		}
		if (backslash_word(&sh->line[i]) > 0)
			i++;
		i++;
	}
	return (0);
}
