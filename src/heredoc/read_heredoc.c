#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"
#include "../../inc/sh21.h"

static inline char	*ft_new_line(char **str)
{
	int nb;
	char *ret;
	int i;

	nb = ft_strlen(*str);
	i = 0;
	if (!(ret = (char*)malloc(sizeof(char) * (nb + 2))))
		return (NULL);
	while ((*str)[i])
	{
		ret[i] = (*str)[i];
		i++;
	}
	ret[i] = '\n';
	ret[i + 1] = 0;
	free(*str);
	return (ret);
}

static inline void ft_display_prompt_quotes(t_termc *tsh)
{
	int 		i;
	char 		*prompt;

	ft_free_dlist(&tsh->line);
	tsh->line->lnk_before = 0;
	prompt = "heredoc> ";
	i = -1;
	while (prompt[++i])
		push_backdlst(tsh->line, prompt[i], 0);
	i = 0;
	while (i < (int)tsh->console->total_line)
	{
		tputs(tsh->term->dostr, 1, ft_inputstr);
		i++;
	}
	ft_display(tsh);
}

static inline char	*ft_readline_hdoc(t_termc *t)
{
	long	c;

	c = 0;
	ft_display_prompt_quotes(t);
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
		ft_display(t);
	}
	if (t->console->total_line < 1)
		ft_putchar('\n');
	return (ft_to_str(t, 1));
}

char  *ft_line_hdoc(char *end)
{
	int 	opt;
	char 	*tmp;
	char 	*line;
	char 	*line_tmp;
	t_termc *tsh;

	tsh = ft_ret_tsh(NULL);
	opt = 0;
	tsh->hdoc = 1;
	tsh->console->total_line = 0;
	while ((line = ft_readline_hdoc(tsh)) != NULL)
	{
		line_tmp = line;
		if (!tsh->hdoc)
		{
			if (tmp)
				free(tmp);
			return (line);
		}
		if (opt == 1)
		{
			opt = 0;
			line = ft_free_join(tmp, line, 'B');
		}
		if (!ft_strcmp(line_tmp, end))
		{
			ft_putchar('\n');
			break ;
		}
		else
		{
			tmp = ft_new_line(&line);
			opt = 1;
		}
	}
	return (line);
}
