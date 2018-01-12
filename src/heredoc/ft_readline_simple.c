#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"
#include "../../inc/sh21.h"

static inline void ft_display_prompt_simple(t_termc *tsh, char *prompt)
{
	int 		i;

	ft_free_dlist(&tsh->line);
	tsh->console->total_line = 0;
	tsh->line->lnk_before = 0;
	tsh->r_other = 1;
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

char	*ft_readline_simple(char *prompt)
{
	t_termc *tsh;
	long	c;

	c = 0;
	tsh = ft_ret_tsh(NULL);
	ft_display_prompt_quotes(t, prompt);
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
