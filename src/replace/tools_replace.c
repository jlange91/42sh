#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"
#include "../../inc/globbing.h"
#include "../../inc/sh21.h"

void    push_dupdlst(dlist *line, int c, int pos, int index)
{
	t_lineterm	*new;

	new = NULL;
	if ((new = (t_lineterm *)malloc(sizeof(t_lineterm))) == NULL)
		exit(1);
	new->c = (char)c;
	new->under = 0;
	new->index = index;
	new->s_pos = pos;
	new->next = NULL;
	new->prev = line->end;
	if (line->end)
		line->end->next = new;
	else
		line->begin = new;
	line->end = new;
}

void    ft_freedlnk(dlist *line)
{
	t_lineterm  *del;
	t_lineterm  *elem;

	elem = line->end;
	if (elem != NULL)
	{
		while (elem)
		{
			del = elem;
			elem = elem->prev;
			free(del);
		}
		line->begin = NULL;
		line->end = NULL;
		return ;
	}
}

void ft_dupdlnk(dlist *line, dlist *tmp)
{
	t_lineterm 	*begin;

	begin = line->begin;
	begin = ft_dontGetPrompt2(begin);
	while (begin)
	{
		push_dupdlst(tmp, begin->c, begin->s_pos, begin->index);
		begin = begin->next;
	}
}

void 	ft_cpy_to_line(char *data, t_termc *tsh)
{
	int i;

	i = -1;
	tsh->autoc->updaterow = 0;
	while (data[++i])
		push_backdlst(tsh->line, data[i], 1);
}

int 		ft_word_here(t_lineterm *begin, char *word)
{
	int 	i;

	i = 0;
	while (word[i])
	{
		if (word[i] == begin->c)
		{
			if (begin && begin->next)
				begin = begin->next;
		}
		else
			break ;
		i++;
	}
	if (word[i] == '\0' && ((begin && begin->s_pos == 0) || !begin->next))
		return (1);
	return (0);
}
