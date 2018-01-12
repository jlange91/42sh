#include "../../inc/quote.h"
#include "../../inc/line_edition.h"

t_lineterm *ft_dont_get_prompt(t_lineterm *tmp)
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

static inline int		ft_fill_prompt_quotes(dlist *line, int ret)
{
	char	*str;
	int		i;

	str = NULL;
	if (ret == -1)
		str = "dquote > ";
	else if (ret == -2)
		str = "quote > ";
	else if (ret == -3)
		str = "bquote > ";
	else if (ret == -4)
		str = "> ";
	if (str)
	{
		i = -1;
		while (str[++i])
			push_backdlst(line, str[i], 0);
		return (1);
	}
	return (0);
}

char 		*ft_skel_quote(char **wrd, int flag)
{
	static char *new;

	if (flag)
	{
		ft_strdel(&new);
		return (NULL);
	}
	if (!wrd || !(*wrd))
		return (new);
	*wrd = ft_free_join(*wrd, "\n", 'L');
	ft_join_all(*wrd, &new, 1);
	return (new);
}

int ft_line_quotes(t_termc *t) 				// LEAKS ==> MUST FREE TMP
{
	char 		*tmp;
	static int  ret;
	int 		i;

	if (!t->quotes)
	{
		tmp = ft_to_str(t, 0);
		ret = ft_check_quote(tmp);
	}
	if (ret != 1)
	{
		t->quotes = 1;
		i = 0;
		tmp = ft_to_str(t, 1);
		while (i < (int)t->console->total_line)
		{
			tputs(t->term->dostr, 1, ft_inputstr);
			i++;
		}
		tmp = ft_skel_quote(&tmp, 0);
		ret = ft_check_quote(tmp);
		if (ret == 0)
		{
			tputs(t->term->upstr, 1, ft_inputstr);
			return (0);
		}
		else
		{
			ft_free_dlist(&t->line);
			ft_fill_prompt_quotes(t->line, ret);
			return (1);
		}
	}
	return (0);
}
