#include "../../inc/quote.h"
#include "../../inc/line_edition.h"

static t_lineterm *ft_dont_get_prompt(t_lineterm *tmp)
{
	while (tmp)
	{
        if (tmp->c == '>')
        {
            tmp = tmp->next;
            break;
        }
		tmp = tmp->next;
    }
    tmp = tmp->next;
	return (tmp);
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

static int		ft_fill_prompt_quotes(dlist *line, int ret)
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

char	*ft_line_input_quotes(t_termc *sh, int ret)
{
	long	c;
	int		nbr;

	c = 0;
	nbr = 0;
	sh->line->lnk_before = 0;
	ft_free_dlist(&sh->line);
	ft_fill_prompt_quotes(sh->line, ret);
	while (read(0, &c, sizeof(c)))
	{
		if (c == '\n')
			break;
		if ((ft_is_key(sh->line, sh, c) == 0 && ft_isprint((char)c)))
		{
			(sh->line->lnk_before) ? ft_insert_dlnk(sh->line->end, sh, c, 1) :
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
