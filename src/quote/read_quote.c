#include "../../inc/quote.h"
#include "../../inc/line_edition.h"

static inline t_lineterm *ft_dont_get_prompt(t_lineterm *tmp)
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

static inline char  *ft_getstr(t_termc *tsh, t_lineterm *begin)
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
	str = (char *)malloc(sizeof(char) * (ft_count_dlnk(tsh) + 2));
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

static inline int		ft_fill_prompt_quotes(dlist *line, int ret)
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
            push_backdlst(line, str[i], 0);
        free(str);
        return (1);
    }
    return (0);
}

static inline void ft_display_prompt_quotes(t_termc *tsh, int ret)
{
	int 		i;

	tsh->line->lnk_before = 0;
	ft_free_dlist(&tsh->line);
	ft_fill_prompt_quotes(tsh->line, ret);
	i = 0;
	while (i < (int)tsh->console->total_line)
	{
		tputs(tsh->term->dostr, 1, ft_inputstr);
		i++;
	}
	ft_display(tsh, 0);
}

char	*ft_line_input_quotes(t_termc *t, int ret)
{
	long	c;

	if (t->sigint)
		return (NULL);
	c = 0;
	ft_display_prompt_quotes(t, ret);
	while (read(0, &c, sizeof(c)))
	{
		if (c == '\n')
			break ;
		if ((ft_is_key(t->line, t, c) == 0 && ft_isprint((char)c)))
		{
			(t->line->lnk_before) ? ft_insert_dlnk(t->line->end, t, c, 1) :
			push_backdlst(t->line, c, 1);
		}
		else
			t->line->lnk_before = 1;
		if (t->line->last)
			t->line->lnk_before = 0;
		c = 0;
		ft_display(t, 0);
	}
	if (t->console->total_line < 1)
		ft_putchar('\n');
	return (ft_getstr(t, t->line->begin));
}
