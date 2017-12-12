#include "../../inc/quote.h"
#include "../../inc/line_edition.h"

static void	display_missing_quote(int opt)
{
	if (opt == -1)
		ft_putstr("\ndquote > ");
	else if (opt == -2)
		ft_putstr("\nquote > ");
	else if (opt == -3)
		ft_putstr("\nbquote > ");
	else if (opt == -4)
		ft_putstr("\n> ");
}

static char	*ft_new_line(char *str)
{
	int nb;
	char *ret;
	int i;

	nb = ft_strlen(str);
	i = 0;
	if (!(ret = (char*)malloc(sizeof(char) * (nb + 2))))
		return (NULL);
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\n';
	ret[i + 1] = 0;
	return (ret);
}

char 	*ft_get_line(t_termc *sh, char *tmp, int ret)
{
	char 	*line;
	int 	opt;

	opt = 1;
	while (1)
	{
		line = ft_line_input_quotes(sh, ret);
		if (opt == 1)
		{
			opt = 0;
			line = ft_free_join(tmp, line, 'B');
		}
		ret = ft_check_quote(line);
		if (ret == 0)
			break;
		else
		{
			tmp = ft_new_line(line);
			display_missing_quote(ret);
			free(line);
			opt = 1;
		}
	}
	return (line);
}

void	ft_fill_line(t_termc *sh)
{
	int 	ret;
	char 	*tmp;
	char 	*line;

	ret = 0;
	line = ft_line_input(sh);
	ft_end_term(sh);
	if ((ret = ft_check_quote(line)) != 0)
	{
		sh->quotes = 1;
		tmp = ft_strjoin(line, "\n");
		display_missing_quote(ret);
		ft_init_terminal_mode(sh);
		free(line);
		line = ft_get_line(sh, tmp, ret);
	}
	sh->line_shell = ft_strdup(line);
	free(line);
}
