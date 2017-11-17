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

static inline char  *ft_getstr2(t_termc *shell, t_lineterm *begin)
{
	t_lineterm *tmp;
	char        *str;
	int         i;

	tmp = begin;
	i = 0;
	str = NULL;
	if (!tmp)
		return (NULL);
	else if (tmp->next)
		tmp = ft_dont_get_prompt(tmp);
	str = (char *)malloc(sizeof(char) * (ft_count_dlnk(shell) + 2));
	if (!str)
		return (NULL);
	while (tmp)
	{
		str[i] = tmp->c;
		tmp = tmp->next;
		i++;
	}
	str[i] = '\0';
	return (str);
}

int		ft_fill_prompt_quotes(dlist *line, int ret)
{
    char	*str;
    int		i;

    str = NULL;
	if (ret == -1)
    	str = ft_strdup("dquote > ");
	else if (ret == -2)
    	str = ft_strdup("quote > ");
	else if (ret == -3)
    	str = ft_strdup("bquote > ");
	else if (ret == -4)
    	str = ft_strdup("> ");
    if (str)
    {
        i = -1;
        while (str[++i])
            ft_fill_back_dlst(line, str[i], 0);
        free(str);
        return (1);
    }
    return (0);
}

char	*ft_line_input_quotes(t_termc *sh, char **env, int ret)
{
	long	c;
	int		i;
	int		nbr = 0;

	c = 0;
	i = -1;
	sh->line->lnk_before = 0;
	ft_free_dlist(&sh->line);
	ft_fill_prompt_quotes(sh->line, ret);
	while (read(0, &c, sizeof(c)))
	{
		if (c == '\n')
			break;
		if ((ft_is_key(sh->line, sh, c, env) == 0 && ft_isprint((char)c)))
		{
			if (sh->line->lnk_before)
				ft_insert_dlnk(sh->line->end, sh, c, 1);
			else
				ft_fill_back_dlst(sh->line, c, 1);
		}
		else
			sh->line->lnk_before = 1;
		if (sh->line->last)
			sh->line->lnk_before = 0;
		c = 0;
		ft_display(sh, &nbr, 0);
	}
	return (ft_getstr2(sh, sh->line->begin));
}

void	ft_remove_space(char *str)
{
	char	*tmp;

	tmp = ft_strtrim(str);
	free(str);
	str = ft_strdup(tmp);
	free(tmp);
}

void	ft_fill_line(t_termc *sh, char **env)
{
	int 	ret;
	char 	*tmp;
	int 	opt;
	char 	*line;

	ret = 0;
	opt = 0;
	line = ft_line_input(sh, env);
	ft_end_term(sh);
	if ((ret = ft_check_quote(line)) != 0)
	{
		sh->quotes = 1;
		tmp = ft_strjoin(line, "\n");
		display_missing_quote(ret);
		ft_init_terminal_mode(sh);
		free(line);
		opt = 1;
		while (1)
		{
			line = ft_line_input_quotes(sh, env, ret);
			ft_remove_space(line);
			if (opt == 1)
			{
				sh->line_shell = ft_strjoin(tmp, line);
				free(tmp);
				free(line);
				opt = 0;
				line = ft_strdup(sh->line_shell);
				free(sh->line_shell);
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
	}
	sh->line_shell = ft_strdup(line);
	free(line);
}
