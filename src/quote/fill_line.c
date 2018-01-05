#include "../../inc/quote.h"
#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"

static inline char	*ft_new_line(char *str)
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

static inline void ft_get_line(t_termc *tsh, char *tmp, int ret, char **line)
{
	int 	opt;

	opt = 1;
	while ((*line = ft_readline_quotes(tsh, ret)) != NULL)
	{
		if (tmp && !tsh->quotes)
		{
			free(tmp);
			break ;
		}
		if (opt == 1)
		{
			opt = 0;
			*line = ft_free_join(tmp, *line, 'B');
		}
		if ((ret = ft_check_quote(*line)) == 0)
		{
			ft_putchar('\n');
			break ;
		}
		else
		{
			tmp = ft_new_line(*line);
			free(*line);
			opt = 1;
		}
	}
}

void	ft_fill_line(t_termc *tsh)
{
	int 	ret;
	char 	*tmp;
	char 	*line;

	ret = 0;
	line = ft_readline(tsh);
	if ((ret = ft_check_quote(line)) != 0)
	{
		tsh->quotes = 1;
		tsh->console->total_line = 0;
		tmp = NULL;
		tmp = ft_free_join(line, "\n", 'L');
		ft_get_line(tsh, tmp, ret, &line);
		if (tsh->sigint)
		{
			tsh->line_shell = ft_to_str(tsh, 0);
			if (line)
				free(line);
			ft_putchar('\n');
			return ;
		}
	}
	tsh->line_shell = ft_strdup(line);
	free(line);
}
